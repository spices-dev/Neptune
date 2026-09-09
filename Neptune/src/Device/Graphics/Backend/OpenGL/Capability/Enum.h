/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

namespace Neptune::OpenGL {

    /**
    * @brief Enum of Capability.
    */
    enum class ECapability : uint8_t
    {
        DirectStateAccess = 0,             // @brief DirectStateAccess.
        BufferStorage,                     // @brief BufferStorage.
        ComputeShader,                     // @brief ComputeShader.
        MultiDrawIndirect,                 // @brief MultiDrawIndirect.
        IndirectParameters,                // @brief IndirectParameters.
        ShaderDrawParameters,              // @brief ShaderDrawParameters.
        ShaderStorageBufferObject,         // @brief ShaderStorageBufferObject.
        BindlessTexture,                   // @brief BindlessTexture.
        Spirv,                             // @brief Spirv.
        SeparateShaderObjects,             // @brief SeparateShaderObjects.
        ParallelShaderCompile,             // @brief ParallelShaderCompile.
        ClipControl,                       // @brief ClipControl.
        ConservativeRaster,                // @brief ConservativeRaster.
        TextureView,                       // @brief TextureView.
        TextureBarrier,                    // @brief TextureBarrier.
        TextureFilterAnisotropic,          // @brief TextureFilterAnisotropic.
        SparseTexture,                     // @brief SparseTexture.
        MeshShader,                        // @brief MeshShader.
        ShadingRateImage,                  // @brief ShadingRateImage.
        ShaderSubGroup,                    // @brief ShaderSubGroup.
        ShaderGroupVote,                   // @brief ShaderGroupVote.
        ShaderInt64,                       // @brief ShaderInt64.
        FragmentShaderInterlock,           // @brief FragmentShaderInterlock.
        ShaderViewportLayerArray,          // @brief ShaderViewportLayerArray.
        MemoryObject,                      // @brief MemoryObject.
        Semaphore,                         // @brief Semaphore.
        Debug,                             // @brief Debug.
        TimerQuery,                        // @brief TimerQuery.
        PipelineStatisticsQuery,           // @brief PipelineStatisticsQuery.
        GetProgramBinary,                  // @brief GetProgramBinary.
        Robustness,                        // @brief Robustness.
        ES32Compatibility,                 // @brief ES32Compatibility.
        FragmentShaderBarycentric,         // @brief FragmentShaderBarycentric.
        InvalidateSubdata,                 // @brief InvalidateSubdata.
        MultiBind,                         // @brief MultiBind.
        QueryBufferObject,                 // @brief QueryBufferObject.
        TimelineSemaphore,                 // @brief TimelineSemaphore.
        VertexAttribBinding,               // @brief VertexAttribBinding.
        KeydMutex,                         // @brief KeydMutex.
        
        Count
    };
    
    inline std::string ToString(ECapability e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum ECapability;
        
        switch (e)
        {
            default:                              return "NonNamed";
        }
    }

}

#endif