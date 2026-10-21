/**
* @file TransparentSortPassRadixHistogram.comp.slang.
* @brief This Shader Defines TransparentSorPasstRadixHistogram Compute Shader Behaver.
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

groupshared uint sHist[256];

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
    uint tid = groupThreadID.x;
    uint wg  = groupID.x;

    TileEntries src  = (TileEntries)push.srcAddress;
    uint        base = wg * RADIX_ELEMS_PER_WG + tid;
    const uint  MAXIDX = MAXTILEGAUSSIANS - 1u;
    uint64_t    e0   = src[min(base,          MAXIDX)];
    uint64_t    e1   = src[min(base + 256u,   MAXIDX)];
    uint64_t    e2   = src[min(base + 512u,   MAXIDX)];
    uint64_t    e3   = src[min(base + 768u,   MAXIDX)];

    TileSortInfos info = (TileSortInfos)push.infoAddress;
    uint numElements   = info[0].numElements;
    uint numWG         = info[0].numWG;
    
    sHist[tid] = 0u;
    GroupMemoryBarrierWithGroupSync();

    uint shift = push.shift;
    if (base            < numElements) InterlockedAdd(sHist[Digit(e0, shift)], 1u);
    if (base + 256u     < numElements) InterlockedAdd(sHist[Digit(e1, shift)], 1u);
    if (base + 512u     < numElements) InterlockedAdd(sHist[Digit(e2, shift)], 1u);
    if (base + 768u     < numElements) InterlockedAdd(sHist[Digit(e3, shift)], 1u);

    GroupMemoryBarrierWithGroupSync();

    ((TileUints)push.histAddress)[tid * numWG + wg] = sHist[tid];
}

/*****************************************************************************************/