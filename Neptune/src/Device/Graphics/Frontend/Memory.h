/**
* @file Memory.h.
* @brief The Memory Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Enum.h"

namespace Neptune::Graphic {
    
    /**
    * @brief MemoryBarrier Description.
    */
    struct MemoryBarrierDesc
    {
        EPipelineAccess srcAccess;      // @brief src EPipelineAccess.
        EPipelineAccess dstAccess;      // @brief dst EPipelineAccess.
        
        EPipelineStage srcStage;        // @brief src EPipelineStage.
        EPipelineStage dstStage;        // @brief dst EPipelineStage.
    };

}