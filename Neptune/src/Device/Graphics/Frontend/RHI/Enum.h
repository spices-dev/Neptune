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
    
    inline std::string ToString(ERHI e)
    {
        switch (e)
        {
            case ERHI::Capability:           return "Capability";
            case ERHI::RenderPass:           return "RenderPass";
            case ERHI::DescriptorList:       return "DescriptorList";
            case ERHI::Pipeline:             return "Pipeline";
            case ERHI::Shader:               return "Shader";
            case ERHI::RenderTarget:         return "RenderTarget";
            case ERHI::VertexBuffer:         return "VertexBuffer";
            case ERHI::IndexBuffer:          return "IndexBuffer";
            case ERHI::Buffer:               return "Buffer";
            case ERHI::CmdList:              return "CmdList";
            case ERHI::CmdList2:             return "CmdList2";
            case ERHI::Decoder:              return "Decoder";
            case ERHI::OpticalFlow:          return "OpticalFlow";
            default:                         return "NonNamed";
        }
    }
    
}