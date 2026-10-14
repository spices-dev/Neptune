/**
* @file GS3DTileRenderCommon.glsl.
* @brief This Shader Header File Defines GS3DTileRenderCommon.
* @author Spices.
*/

/************************************Pre Compile*******************************************/
        
#ifndef GS3D_TILERENDER_COMMON_H
#define GS3D_TILERENDER_COMMON_H

#include "GS3DTileRenderCore.h"

/*****************************************************************************************/

/****************************************Buffer Data**************************************/

layout(buffer_reference, scalar, buffer_reference_align = 4)  buffer TileSortInfos { TileSortInfo i[]; };  // @brief TileSortInfo Buffer.
layout(buffer_reference, scalar, buffer_reference_align = 8)  buffer TileEntries   { uint64_t i[]; };      // @brief Sort Buffer.
layout(buffer_reference, scalar, buffer_reference_align = 4)  buffer TileUints     { uint     i[]; };      // @brief hist Buffer.
layout(buffer_reference, scalar, buffer_reference_align = 16) buffer TileSplats    { uvec4 i[]; };         // @brief Splats Buffer. @see Splat.
layout(buffer_reference, scalar, buffer_reference_align = 8)  buffer TileRanges    { uvec2    i[]; };      // @brief Range Buffer.

/*****************************************************************************************/

/******************************************Functions**************************************/

/**
* @brief Make Sort Key.
* 
* @param[in] tile Tile Id.
* @param[in] viewDepth GS ID Depth.
* @param[in] gid GS ID.
* 
* @return Returns Key.
*/
uint64_t MakeSortKey(uint tile, float viewDepth, uint gid)
{
    uint depthKey = (floatBitsToUint(max(viewDepth, 0.0)) >> 7u) & 0xFFFFFFu;

    return (uint64_t(tile) << TILE_SHIFT) | (uint64_t(depthKey) << DEPTH_SHIFT) | uint64_t(gid);
}

/*****************************************************************************************/

#endif
