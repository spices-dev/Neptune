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
static const uint  TILE_SIZE                 = 16u;                                                                                   // @brief Tile Render Size.
static const float RADIUS_SIGMA              = 3.0f;                                                                                  // @brief Splat Radius Sigma.
static const uint  GID_BITS                  = 24u;                                                                                   // @brief GS id bits.
static const uint  MAXGAUSSIANS              = 1u << GID_BITS;                                                                        // @brief GS Max Count.
static const uint  DEPTH_BITS                = 24u;                                                                                   // @brief Depth bits.
static const uint  TILEID_BITS               = 16u;                                                                                   // @brief Tile id bits.
static const uint  GID_SHIFT                 = 0u;                                                                                    // @brief GS id shift.
static const uint  DEPTH_SHIFT               = GID_BITS;                                                                              // @brief Depth shift.
static const uint  TILE_SHIFT                = DEPTH_BITS + GID_BITS;                                                                 // @brief Tile shift.
static const uint  GID_MASK                  = ((1u << GID_BITS) - 1u);                                                               // @brief GS id mask.
static const uint  RADIX_FIRST_BIT           = DEPTH_SHIFT;                                                                           // @brief Radix First bits.
static const uint  RADIX_DIGITAL_BIT         = 8u;                                                                                    // @brief Radix Digital bits.
static const uint  RADIX_NUM_PASSES          = (64u - RADIX_FIRST_BIT + RADIX_DIGITAL_BIT - 1u) / RADIX_DIGITAL_BIT;                  // @brief Radix Passes.
static const uint  RADIX_ELEMS_PER_WG        = 1024u;                                                                                 // @brief Radix Handled Splats Count Per WorkGroup.
static const uint  AVGTILESPERGAUSSIAN       = 1u;                                                                                    // @brief Avg GS Count Per Tile.
static const uint  MAXTILEGAUSSIANS          = MAXGAUSSIANS * AVGTILESPERGAUSSIAN;                                                    // @brief Max Tile GS Count.
static const uint  MAXTILEGAUSSIANSNUMWG     = (MAXTILEGAUSSIANS + RADIX_ELEMS_PER_WG - 1u) / RADIX_ELEMS_PER_WG;                     // @brief Max Tile GS WorkGroup Count.
static const uint  MAXTILESX                 = (3840u + TILE_SIZE - 1u) / TILE_SIZE;                                                  // @brief Max Tiles in X.
static const uint  MAXTILESY                 = (2160u + TILE_SIZE - 1u) / TILE_SIZE;                                                  // @brief Max Tiles in Y.
static const uint  MAXTILES                  = MAXTILESX * MAXTILESY;                                                                 // @brief Max Tiles Count.
    
/*****************************************************************************************/

/***********************************SOP Description Data**********************************/

/**
* @brief GS3D Description Struct.
*/
struct GS3DDesc
{
	uint64_t modelAddress;                    /* @brief Address of the Model Matrix.                      */
    uint64_t meansRangesAddress;              /* @brief Address of meansRanges Buffer.                    */
    uint64_t scaleCodesAddress;               /* @brief Address of ScaleCodes Buffer.                     */
    uint64_t sh0CodesAddress;                 /* @brief Address of sh0Codes Buffer.                       */
	uint     means0Address;                   /* @brief Address of the Positions Texture.                 */
	uint     means1Address;                   /* @brief Address of the Positions Texture.                 */
	uint     scalesAddress;                   /* @brief Address of the Scales Texture.                    */
	uint     quatsAddress;                    /* @brief Address of the Orientations Texture.              */
	uint     sh0Address;                      /* @brief Address of the SH Texture.                        */
	uint     entityID;                        /* @brief EntityId, cast from entt::entity.                 */
};

/*****************************************************************************************/
    
/****************************************GS3D Data***************************************/
    
/**
* @brief Splat Data.
* x : center.x
* y : center.y
* z : eigenvalue 1 of the conic
* w : angle of eigenvector
*/
struct Splat
{
    uint4 packed;            // @brief Packed GS data.
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
    uint     imageWidth;          // @brief GS imageWidth.
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
    uint64_t sh0CodesAddress;     // @brief Address of sh0Codes Buffer.
    uint     tilesX;              // @brief Tiles in X.
    uint     width;               // @brief RenderTarget Width.
    uint     height;              // @brief RenderTarget Height.
};
    
/*****************************************************************************************/
    
#ifdef __cplusplus
}
#endif

#endif