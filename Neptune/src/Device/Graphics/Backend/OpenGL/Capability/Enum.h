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
        DirectStateAccess = 0,
        BufferStorage,
        ComputeShader,
        MultiDrawIndirect,
        IndirectParameters,
        ShaderDrawParameters,
        ShaderStorageBufferObject,
        BindlessTexture,
        Spirv,
        SeparateShaderObjects,
        ParallelShaderCompile,
        ClipControl,
        ConservativeRaster,
        TextureView,
        TextureBarrier,
        TextureFilterAnisotropic,
        SparseTexture,
        
        
        
        
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