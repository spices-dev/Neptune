/**
* @file Memory.h.
* @brief The Memory Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/BitSet.h"
#include "Enum.h"

namespace Neptune::Graphic {
    
    /**
    * @brief MemoryBarrier Description.
    */
    struct MemoryBarrierDesc
    {
        Container::BitSet<EPipelineAccess> srcAccess;      // @brief src EPipelineAccess.
        Container::BitSet<EPipelineAccess> dstAccess;      // @brief dst EPipelineAccess.
        
        Container::BitSet<EPipelineStage> srcStage;        // @brief src EPipelineStage.
        Container::BitSet<EPipelineStage> dstStage;        // @brief dst EPipelineStage.
    };
    
    /**
    * @brief ImageBarrier Description.
    */
    struct ImageBarrierDesc
    {
        MemoryBarrierDesc memoryDesc;                                   // @brief MemoryBarrierDesc.
        EImageLayout      srcLayout;                                    // @brief src EImageLayout.
        EImageLayout      dstLayout;                                    // @brief dst EImageLayout.
        EImageAspect      aspect           = EImageAspect::Color;       // @brief EImageAspect.
        uint32_t          baseMipLevel     = 0;                         // @brief baseMipLevel.
        uint32_t          levelCount       = 1;                         // @brief levelCount.
        uint32_t          baseArrayLayer   = 0;                         // @brief baseArrayLayer.
        uint32_t          layerCount       = 1;                         // @brief layerCount.
    };

}