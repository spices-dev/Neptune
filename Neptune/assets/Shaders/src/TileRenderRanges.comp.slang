/**
* @file TileRenderRanges.comp.slang.
* @brief This Shader Defines TileRenderRanges Compute Shader Behaver.
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
[[vk::push_constant]] ConstantBuffer<RangePush> push;

static const uint NO_TILE = 0xFFFFFFFFu;             // Sentinel: differs from every real tile id.

groupshared uint sTile[RADIX_ELEMS_PER_WG + 2u];   // sTile[s] = tile of element (wg * 1024 + s - 1).

/*****************************************************************************************/
        
/**********************************Functions**********************************************/

uint LoadTile(TileEntries e, uint g, uint n)
{
    return (g >= 1u && g - 1u < n) ? uint(e[g - 1u] >> TILE_SHIFT) : NO_TILE;
}

/*****************************************************************************************/
        
/**********************************Shader Entry*******************************************/

[shader("compute")]
[numthreads(256, 1, 1)]
void main(uint3 groupThreadID : SV_GroupThreadID, uint3 groupID : SV_GroupID)
{
    TileSortInfos infos = (TileSortInfos)push.infoAddress;
    uint n   = infos[0].numElements;
    uint tid = groupThreadID.x;
    uint wg  = groupID.x;
    
    TileEntries e = (TileEntries)push.sortedAddress;
    TileRanges  r = (TileRanges)push.rangeAddress;

    uint g0 = wg * RADIX_ELEMS_PER_WG + tid;
    uint t0 = LoadTile(e, g0,         n);
    uint t1 = LoadTile(e, g0 + 256u,  n);
    uint t2 = LoadTile(e, g0 + 512u,  n);
    uint t3 = LoadTile(e, g0 + 768u,  n);
    uint t4 = (tid < 2u) ? LoadTile(e, g0 + 1024u, n) : NO_TILE;

    sTile[tid]         = t0;
    sTile[tid + 256u]  = t1;
    sTile[tid + 512u]  = t2;
    sTile[tid + 768u]  = t3;
    if (tid < 2u) sTile[tid + 1024u] = t4;

    GroupMemoryBarrierWithGroupSync();

    for (uint k = 0u; k < 4u; ++k)
    {
        uint s   = k * 256u + tid + 1u;
        uint idx = wg * RADIX_ELEMS_PER_WG + k * 256u + tid;
        if (idx >= n) continue;
        
        uint tile = sTile[s];
        if (tile >= push.numTiles) continue;
            
        if (sTile[s - 1u] != tile) r[tile].x = idx;
        if (sTile[s + 1u] != tile) r[tile].y = idx + 1u;
    }
}

/*****************************************************************************************/