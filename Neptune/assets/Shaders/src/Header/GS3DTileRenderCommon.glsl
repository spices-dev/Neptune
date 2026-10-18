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

/**
* @brief Make PackSplat.
* 
* @param[in] center .
* @param[in] conic .
* @param[in] sh0Raw .
* 
* @return Returns PackSplat.
*/
uvec4 PackSplat(vec2 center, vec3 conic, uvec4 sh0Raw)
{
    const float PI_F = 3.14159265358979;

    ivec2 ci = clamp(ivec2(round(center * 64.0)), ivec2(-2097152), ivec2(2097151));
    uvec2 cu = uvec2(ci) & 0x3FFFFFu;
    
    float mid = 0.5 * (conic.x + conic.z);
    float dif = 0.5 * (conic.x - conic.z);
    float rad = sqrt(dif * dif + conic.y * conic.y);
    float l1  = mid + rad;
    float l2  = max(mid - rad, 0.0);
    float th  = (rad > 0.0) ? 0.5 * atan(2.0 * conic.y, conic.x - conic.z) : 0.0;
    if (th < 0.0) th += PI_F;
    uint  ang = uint(round(th * (65536.0 / PI_F))) & 0xFFFFu;

    uint k = 0u;
    if (l1 > 0.0 && l1 < 1.0) k = uint(min(15.0, floor(-0.5 * log2(l1))));
    vec2 ls = vec2(l1, l2) * exp2(float(2u * k));

    uvec3 c8 = sh0Raw.rgb & 0xFFu;

    uint w0 = cu.x | ((sh0Raw.a & 0xFFu) << 22u) | ((k & 3u)  << 30u);
    uint w1 = cu.y | (c8.x << 22u)               | ((k >> 2u) << 30u);
    uint w2 = packHalf2x16(ls);
    uint w3 = ang | (c8.y << 16u) | (c8.z << 24u);
    return uvec4(w0, w1, w2, w3);
}

/**
* @brief Unpack PackSplat.
* 
* @param[in] s Splat.
* @param[out] center .
* @param[out] conic.
* @param[out] opacity.
*/
void UnpackSplat(uvec4 s, out vec2 center, out vec3 conic, out float opacity)
{
    const float PI_F = 3.14159265358979;

    center  = vec2(float(int(s.x << 10u) >> 10), float(int(s.y << 10u) >> 10)) * (1.0 / 64.0);
    opacity = float((s.x >> 22u) & 0xFFu) / 255.0;

    uint  k     = (s.x >> 30u) | ((s.y >> 30u) << 2u);
    float scale = uintBitsToFloat((127u - 2u * k) << 23u);              // 2^(-2k)
    vec2  lam   = unpackHalf2x16(s.z) * scale;

    float th    = float(s.w & 0xFFFFu) * (PI_F / 65536.0);
    float cs    = cos(th);
    float sn    = sin(th);
    conic       = vec3(lam.x * cs * cs + lam.y * sn * sn,
                      (lam.x - lam.y) * cs * sn,
                       lam.x * sn * sn + lam.y * cs * cs);
}

/**
* @brief Unpack SplatSh0.
* 
* @param[in] s Splat.
* 
* @return Returns Sh0.
*/
uvec3 UnpackSplatSh0(uvec4 s)
{
    return uvec3((s.y >> 22u) & 0xFFu, (s.w >> 16u) & 0xFFu, s.w >> 24u);
}

/*****************************************************************************************/

#endif
