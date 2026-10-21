/**
* @file TransparentSortPassRadixScan.comp.slang.
* @brief This Shader Defines TransparentSortPassRadixScan Compute Shader Behaver.
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

groupshared uint sWarp[2][8];      // @brief Warp totals

/*****************************************************************************************/

/**********************************Shader Entry*******************************************/
        
[shader("compute")]
[numthreads(256, 1, 1)]
void main(uint3 groupThreadID : SV_GroupThreadID, uint3 groupID : SV_GroupID)
{
    TileSortInfos infos = (TileSortInfos)push.infoAddress;
    uint numWG = infos[0].numWG;
        
    uint tid   = groupThreadID.x;
    uint digit = groupID.x;
    uint warp  = tid >> 5u;
    uint lane  = tid & 31u;

    TileUints h = (TileUints)push.histAddress;
    uint base   = digit * numWG;
        
    uint carry = 0u;
    uint par   = 0u;

    for (uint b0 = 0u; b0 < numWG; b0 += 1024u)
    {
        uint i0 = b0 + tid;
        uint v[4];
        v[0] = (i0         < numWG) ? h[base + i0        ] : 0u;
        v[1] = (i0 + 256u  < numWG) ? h[base + i0 + 256u ] : 0u;
        v[2] = (i0 + 512u  < numWG) ? h[base + i0 + 512u ] : 0u;
        v[3] = (i0 + 768u  < numWG) ? h[base + i0 + 768u ] : 0u;
        
        for (uint k = 0u; k < 4u; ++k)
        {
            uint incl = WavePrefixSum(v[k]) + v[k];
            if (lane == 31u) sWarp[par][warp] = incl;
            GroupMemoryBarrierWithGroupSync();
            
            uint wp = 0u, tot = 0u;
            for (uint w = 0u; w < 8u; ++w)
            {
                uint t = sWarp[par][w];
                if (w < warp) wp += t;
                tot += t;
            }
            
            uint idx = i0 + k * 256u;
            if (idx < numWG) h[base + idx] = carry + wp + incl - v[k];
            
            carry += tot;
            par   ^= 1u;
        }
    }
        
    if (tid == 0u) h[256u * numWG + digit] = carry;
}

/*****************************************************************************************/