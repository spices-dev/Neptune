/**
* @file Memory.h.
* @brief The Memory Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Pipeline Access.
    */
    enum class EPipelineAccess : uint8_t
    {
        ShaderRead = 0,              // @brief ShaderRead.
        ShaderWrite,                 // @brief ShaderWrite.
        
        Count
    };
    
    /**
    * @brief Enum of Pipeline Stage.
    */
    enum class EPipelineStage : uint8_t
    {
        VertexShader = 0,         // @brief VertexShader.
        FragmentShader,           // @brief FragmentShader.
        ComputeShader,            // @brief ComputeShader.
        
        Count
    };
    
    /**
    * @brief MemoryBarrier Description.
    */
    struct MemoryBarrierdDesc
    {
        EPipelineAccess srcAccess;      // @brief src EPipelineAccess.
        EPipelineAccess dstAccess;      // @brief dst EPipelineAccess.
        
        EPipelineStage srcStage;        // @brief src EPipelineStage.
        EPipelineStage dstStage;        // @brief dst EPipelineStage.
    };

}