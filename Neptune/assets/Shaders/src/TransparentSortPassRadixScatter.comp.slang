/**
* @file TransparentSortPassRadixScatter.comp.slang.
* @brief This Shader Defines TransparentSortPassRadixScatter Compute Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#include "Header/PreRendererLayout.slangh"
#include "Header/GS3DTileRenderCommon.slangh"

/*****************************************************************************************/

/********************************Descriptor List******************************************/

/**
* @brief push constant.
*/
[[vk::push_constant]] ConstantBuffer<RadixPush> push;

groupshared uint sWarpTot[8];            // @brief Per-warp sum of the digit totals.
groupshared uint sWarpHist[2][8][256];   // @brief Per sub-tile, per warp, per digit counts, double buffered.

/*****************************************************************************************/

/**********************************Functions**********************************************/
        
uint Digit(uint64_t e, uint shift)
{
    return uint(e >> shift) & 0xFFu;
}

/*****************************************************************************************/
        
/**********************************Shader Entry*******************************************/
        
[shader("compute")]
[numthreads(256, 1, 1)]
void main(uint3 groupThreadID : SV_GroupThreadID, uint3 groupID : SV_GroupID)
{
    uint tid  = groupThreadID.x;
    uint wg   = groupID.x;
    uint warp = tid >> 5u;
    uint lane = tid & 31u;

    TileEntries src = (TileEntries)push.srcAddress;
    TileEntries dst = (TileEntries)push.dstAddress;

    uint idx0 = wg * RADIX_ELEMS_PER_WG + tid;
    const uint MAXIDX = MAXTILEGAUSSIANS - 1u;
    uint64_t key0 = src[min(idx0,         MAXIDX)];
    uint64_t key1 = src[min(idx0 + 256u,  MAXIDX)];
    uint64_t key2 = src[min(idx0 + 512u,  MAXIDX)];
    uint64_t key3 = src[min(idx0 + 768u,  MAXIDX)];
    
    TileSortInfos infos       = (TileSortInfos)push.infoAddress;
    uint          numElements = infos[0].numElements;
    uint          numWG       = infos[0].numWG;
    
    TileUints h = (TileUints)push.histAddress;
    uint total = h[256u * numWG + tid];
    uint pre   = h[tid * numWG + wg];
    
    uint incl = WavePrefixSum(total) + total;
    if (lane == 31u) sWarpTot[warp] = incl;
    for (uint w = 0u; w < 8u; ++w) sWarpHist[0][w][tid] = 0u;
    GroupMemoryBarrierWithGroupSync();
    
    uint warpOff = 0u;
    for (uint w = 0u; w < 8u; ++w) if (w < warp) warpOff += sWarpTot[w];

    uint run = warpOff + incl - total + pre;
    
    for (uint k = 0u; k < 4u; ++k)
    {
        uint p = k & 1u;
        uint q = p ^ 1u;
        
        uint64_t e     = (k == 0u) ? key0 : (k == 1u) ? key1 : (k == 2u) ? key2 : key3;
        uint     idx   = idx0 + k * 256u;
        bool     valid = idx < numElements;
        uint     d     = valid ? Digit(e, push.shift) : 0u;

        uint mask = WaveActiveBallot(valid).x;
        for (uint bit = 0u; bit < 8u; ++bit)
        {
            bool b   = ((d >> bit) & 1u) != 0u;
            uint bal = WaveActiveBallot(b).x;
            mask &= b ? bal : ~bal;
        }
        uint rankW = countbits(mask & ((1u << lane) - 1u));
        uint cntW  = countbits(mask);
        
        if (valid && rankW == 0u) sWarpHist[p][warp][d] = cntW;
        GroupMemoryBarrierWithGroupSync();

        for (uint w = 0u; w < 8u; ++w)
        {
            uint c = sWarpHist[p][w][tid];
            sWarpHist[p][w][tid] = run;
            run += c;
            sWarpHist[q][w][tid] = 0u;
        }
        GroupMemoryBarrierWithGroupSync();
    
        if (valid)
        {
            uint pos = sWarpHist[p][warp][d] + rankW;
            if (pos < numElements) dst[pos] = e;
        }
    }
}

/*****************************************************************************************/