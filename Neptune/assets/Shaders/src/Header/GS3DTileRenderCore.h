/**
* @file GS3DTileRenderCore.h.
* @brief This GS3DTileRenderCore Header File Defines Shader Structure both Shader side and C++ side.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#ifndef GS3D_TILE_RENDER_CORE_H
#define GS3D_TILE_RENDER_CORE_H

#include "Core.h"

#ifdef __cplusplus
namespace Neptune::ShaderCore::GS3DTileRenderCore
{
#endif

/**
* @brief Macros for Variable Constant.
*/
const uint  TILE_SIZE                 = 16u;                                                                                   // @brief Tile Render Size.
const float RADIUS_SIGMA              = 3.0f;                                                                                  // @brief Splat Radius Sigma.
const uint  GID_BITS                  = 24u;                                                                                   // @brief GS id bits.
const uint  MAXGAUSSIANS              = 1u << GID_BITS;                                                                        // @brief GS Max Count.
const uint  DEPTH_BITS                = 24u;                                                                                   // @brief Depth bits.
const uint  TILEID_BITS               = 16u;                                                                                   // @brief Tile id bits.
const uint  GID_SHIFT                 = 0u;                                                                                    // @brief GS id shift.
const uint  DEPTH_SHIFT               = GID_BITS;                                                                              // @brief Depth shift.
const uint  TILE_SHIFT                = DEPTH_BITS + GID_BITS;                                                                 // @brief Tile shift.
const uint  GID_MASK                  = ((1u << GID_BITS) - 1u);                                                               // @brief GS id mask.
const uint  RADIX_FIRST_BIT           = DEPTH_SHIFT;                                                                           // @brief Radix First bits.
const uint  RADIX_DIGITAL_BIT         = 8u;                                                                                    // @brief Radix Digital bits.
const uint  RADIX_NUM_PASSES          = (64u - RADIX_FIRST_BIT + RADIX_DIGITAL_BIT - 1u) / RADIX_DIGITAL_BIT;                  // @brief Radix Passes.
const uint  RADIX_ELEMS_PER_WG        = 1024u;                                                                                 // @brief Radix Handled Splats Count Per WorkGroup.
const uint  AVGTILESPERGAUSSIAN       = 3u;                                                                                    // @brief Avg GS Count Per Tile.
const uint  MAXTILEGAUSSIANS          = MAXGAUSSIANS * AVGTILESPERGAUSSIAN;                                                    // @brief Max Tile GS Count.
const uint  MAXTILEGAUSSIANSNUMWG     = (MAXTILEGAUSSIANS + RADIX_ELEMS_PER_WG - 1u) / RADIX_ELEMS_PER_WG;                     // @brief Max Tile GS WorkGroup Count.
const uint  MAXTILESX                 = (3840u + TILE_SIZE - 1u) / TILE_SIZE;                                                  // @brief Max Tiles in X.
const uint  MAXTILESY                 = (2160u + TILE_SIZE - 1u) / TILE_SIZE;                                                  // @brief Max Tiles in Y.
const uint  MAXTILES                  = MAXTILESX * MAXTILESY;                                                                 // @brief Max Tiles Count.
    
/*****************************************************************************************/

/***********************************SOP Description Data**********************************/

/**
* @brief GS3D Description Struct.
*/
struct GS3DDesc
{
	uint64_t modelAddress;                    /* @brief Address of the Model Matrix.                      */
	uint64_t positionsAddress;                /* @brief Address of the Positions buffer.                  */
	uint64_t colorsAddress;                   /* @brief Address of the Colors buffer.                     */
	uint64_t alphasAddress;                   /* @brief Address of the Alphas buffer.                     */
	uint64_t scalesAddress;                   /* @brief Address of the Scales buffer.                     */
	uint64_t orientationsAddress;             /* @brief Address of the Orientations buffer.               */
	uint64_t sphrsAddress;                    /* @brief Address of the SPH_Rs buffer.                     */
	uint64_t sphgsAddress;                    /* @brief Address of the SPH_Gs buffer.                     */
	uint64_t sphbsAddress;                    /* @brief Address of the SPH_Bs buffer.                     */
	uint64_t normalsAddress;                  /* @brief Address of the Normals buffer.                    */
	uint64_t albedosAddress;                  /* @brief Address of the Albedos buffer.                    */
	uint64_t entityID;                        /* @brief EntityId, cast from entt::entity.                 */
};

/*****************************************************************************************/
    
/****************************************GS3D Data***************************************/
    
/**
* @brief Splat Data.
*/
struct Splat
{
    vec2  center;            // @brief GS Center.
    vec3  conic;             // @brief GS Conic.
    float opacity;           // @brief GS Opacity.
    uvec2 color;             // @brief GS Color.
};

/**
* @brief TileSortInfo Data.
*/
struct TileSortInfo
{
    uint instanceCounter;        // @brief Sort instance Count.
    uint numElements;            // @brief Sort final instance Count.
    uint numWG;                  // @brief Sort WorkGroup Size.
    uint dispatchX;              // @brief WorkGroup dispatch x.
    uint dispatchY;              // @brief WorkGroup dispatch y.
    uint dispatchZ;              // @brief WorkGroup dispatch z.
};
    
/*****************************************************************************************/
    
/******************************************Push Data**************************************/
    
/**
* @brief PreProcessPush Data.
*/
struct PreProcessPush
{
    uint64_t splatAddress;        // @brief Splat Buffer Address.
    uint64_t entryAddress;        // @brief Sort Buffer Address.
    uint64_t infoAddress;         // @brief TileSortInfo Buffer Address.
    uint64_t descAddress;         // @brief GS3DDesc Buffer Address.
    uint     gsCount;             // @brief GS Count.
    uint     tilesX;              // @brief Tiles in X.
    uint     tilesY;              // @brief Tiles in Y.
};

/**
* @brief RadixPush Data.
*/
struct RadixPush
{
    uint64_t srcAddress;      // @brief Sorts Buffer src.
    uint64_t dstAddress;      // @brief Sorts Buffer dst.
    uint64_t histAddress;     // @brief uint[256 * numWG + 256].
    uint64_t infoAddress;     // @brief TileSortInfo.
    uint     shift;           // @brief 24, 32, 40, 48, 56
};

/**
* @brief RangePush Data.
*/
struct RangePush
{
    uint64_t sortedAddress;      // @brief Sorts Buffer Address.
    uint64_t rangeAddress;       // @brief Ranges Buffer Address.
    uint64_t infoAddress;        // @brief TileSortInfo Buffer Address.
    uint     numTiles;           // @brief Tiles Count.
};

/**
* @brief TileRenderPush Data.
*/
struct TileRenderPush
{
    uint64_t splatAddress;        // @brief Splat Buffer Address.
    uint64_t sortedAddress;       // @brief Sorts Buffer Address.
    uint64_t rangeAddress;        // @brief Ranges Buffer Address.
    uint     tilesX;              // @brief Tiles in X.
    uint     width;               // @brief RenderTarget Width.
    uint     height;              // @brief RenderTarget Height.
};
    
/*****************************************************************************************/
    
#ifdef __cplusplus
}
#endif

#endif