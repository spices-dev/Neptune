/**
* @file TileRenderSortSetup.comp.slang.
* @brief This Shader Defines TileRenderSortSetup Compute Shader Behaver.
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
struct SortSetupPush
{
    uint64_t infoAddress;
};

[[vk::push_constant]] ConstantBuffer<SortSetupPush> push;

/*****************************************************************************************/

/**********************************Shader Entry*******************************************/
        
[shader("compute")]
[numthreads(1, 1, 1)]
void main()
{
    TileSortInfos info      = (TileSortInfos)push.infoAddress;

    uint n                  = min(info[0].instanceCounter, MAXTILEGAUSSIANS);
    uint wg                 = (n + RADIX_ELEMS_PER_WG - 1u) / RADIX_ELEMS_PER_WG;
    info[0].numElements     = n;
    info[0].numWG           = wg;
    info[0].dispatchX       = wg;
    info[0].dispatchY       = 1u;
    info[0].dispatchZ       = 1u;
}

/*****************************************************************************************/