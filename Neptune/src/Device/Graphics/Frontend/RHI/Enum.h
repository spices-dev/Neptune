/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::RHI {
    
    /**
    * @brief Enum of RHI.
    */
    enum class ERHI : uint8_t
    {
        Capability,                  // @brief Capability.
        RenderPass,                  // @brief RenderPass.
        DescriptorList,              // @brief DescriptorList.
        Pipeline,                    // @brief Pipeline.
        Shader,                      // @brief Shader.
        RenderTarget,                // @brief RenderTarget.
        VertexBuffer,                // @brief VertexBuffer.
        IndexBuffer,                 // @brief IndexBuffer.
        Buffer,                      // @brief Buffer.
        CmdList,                     // @brief CmdList.
        CmdList2,                    // @brief CmdList2.
        Decoder,                     // @brief Decoder.
        OpticalFlow,                 // @brief OpticalFlow.

        Count
    };
    
}