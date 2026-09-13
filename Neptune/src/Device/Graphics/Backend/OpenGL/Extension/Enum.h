/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

namespace Neptune::OpenGL {

    /**
    * @brief Enum of Extension.
    */
    enum class EExtension : uint8_t
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
        ViewportLayerArray,                // @brief ViewportLayerArray.
        
        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case DirectStateAccess:                     return "DirectStateAccess";
            case BufferStorage:                         return "BufferStorage";
            case ComputeShader:                         return "ComputeShader";
            case MultiDrawIndirect:                     return "MultiDrawIndirect";
            case IndirectParameters:                    return "IndirectParameters";
            case ShaderDrawParameters:                  return "ShaderDrawParameters";
            case ShaderStorageBufferObject:             return "ShaderStorageBufferObject";
            case BindlessTexture:                       return "BindlessTexture";
            case Spirv:                                 return "Spirv";
            case SeparateShaderObjects:                 return "SeparateShaderObjects";
            case ParallelShaderCompile:                 return "ParallelShaderCompile";
            case ClipControl:                           return "ClipControl";
            case ConservativeRaster:                    return "ConservativeRaster";
            case TextureView:                           return "TextureView";
            case TextureBarrier:                        return "TextureBarrier";
            case TextureFilterAnisotropic:              return "TextureFilterAnisotropic";
            case SparseTexture:                         return "SparseTexture";
            case MeshShader:                            return "MeshShader";
            case ShadingRateImage:                      return "ShadingRateImage";
            case ShaderSubGroup:                        return "ShaderSubGroup";
            case ShaderGroupVote:                       return "ShaderGroupVote";
            case ShaderInt64:                           return "ShaderInt64";
            case FragmentShaderInterlock:               return "FragmentShaderInterlock";
            case ShaderViewportLayerArray:              return "ShaderViewportLayerArray";
            case MemoryObject:                          return "MemoryObject";
            case Semaphore:                             return "Semaphore";
            case Debug:                                 return "Debug";
            case TimerQuery:                            return "TimerQuery";
            case PipelineStatisticsQuery:               return "PipelineStatisticsQuery";
            case GetProgramBinary:                      return "GetProgramBinary";
            case Robustness:                            return "Robustness";
            case ES32Compatibility:                     return "ES32Compatibility";
            case FragmentShaderBarycentric:             return "FragmentShaderBarycentric";
            case InvalidateSubdata:                     return "InvalidateSubdata";
            case MultiBind:                             return "MultiBind";
            case QueryBufferObject:                     return "QueryBufferObject";
            case TimelineSemaphore:                     return "TimelineSemaphore";
            case VertexAttribBinding:                   return "VertexAttribBinding";
            case KeydMutex:                             return "KeydMutex";
            case ViewportLayerArray:                    return "ViewportLayerArray";
            default:                                    return "NonNamed";
        }
    }

}

#endif