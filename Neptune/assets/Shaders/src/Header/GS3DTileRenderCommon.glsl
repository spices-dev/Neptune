/**
* @file GS3DTileRenderCommon.glsl.
* @brief This Shader Header File Defines GS3DTileRenderCommon.
* @author Spices.
*/

/************************************Pre Compile*******************************************/
        
#ifndef TILE_RENDER_COMMON_H
#define TILE_RENDER_COMMON_H

const uint  TILE_SIZE          = 16u;
const float RADIUS_SIGMA       = 3.0f;

const uint ENTRY_GID_BITS      = 24u;
const uint ENTRY_DEPTH_BITS    = 24u;
const uint ENTRY_DEPTH_SHIFT   = 24u;
const uint ENTRY_TILE_SHIFT    = 48u;
const uint ENTRY_GID_MASK      = ((1u << ENTRY_GID_BITS) - 1u);
const uint RADIX_FIRST_BIT     = 24u;
const uint RADIX_NUM_PASSES    = 5u;

/*****************************************************************************************/

/****************************************Buffer Data**************************************/

struct Splat
{
    vec2  center;
    vec3  conic;
    float opacity;
    uvec2 color;
};

layout(buffer_reference, scalar, buffer_reference_align = 4) buffer TileSortInfo
{
    uint instanceCounter;
    uint numElements;
    uint numWG;
    uint dispatchX;
    uint dispatchY;
    uint dispatchZ;
};

layout(buffer_reference, scalar, buffer_reference_align = 8) buffer TileEntries { uint64_t i[]; };
layout(buffer_reference, scalar, buffer_reference_align = 4) buffer TileUints   { uint     i[]; };
layout(buffer_reference, scalar, buffer_reference_align = 4) buffer TileSplats  { Splat    i[]; };
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer TileRanges  { uvec2    i[]; };

/*****************************************************************************************/

/******************************************Functions**************************************/

uint64_t PackEntry(uint tile, float viewDepth, uint gid)
{
    uint depthKey = (floatBitsToUint(max(viewDepth, 0.0)) >> 7u) & 0xFFFFFFu;

    return (uint64_t(tile) << ENTRY_TILE_SHIFT) | (uint64_t(depthKey) << ENTRY_DEPTH_SHIFT) | uint64_t(gid);
}

/*****************************************************************************************/

#endif
