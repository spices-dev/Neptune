/**
* @file Capabilities.cpp.
* @brief The Capabilities Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Capabilities.h"
#include "Device/Graphics/Backend/OpenGL/Capability/CapabilityHeader.h"

namespace Neptune::OpenGL {

    Capabilities::Capabilities(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Capabilities::Create()
    {
        NEPTUNE_PROFILE_ZONE

        GLint major = 0;
        GLint minor = 0;
        
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        
        GLint count = 0;
        
        glGetIntegerv(GL_NUM_EXTENSIONS, &count);
        
        for (GLint i = 0; i < count; ++i)
        {
            const auto* name = glGetStringi(GL_EXTENSIONS, static_cast<GLuint>(i));
            
            if (!name) continue;
            
            m_Extensions.emplace_back(reinterpret_cast<const char*>(name));
        }
        
        m_Context.Registry<Capability::IDirectStateAccess>                   (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IBufferStorage>                       (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IComputeShader>                       (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IMultiDrawIndirect>                   (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IIndirectParameters>                  (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShaderDrawParameters>                (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShaderStorageBufferObject>           (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IBindlessTexture>                     (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ISpirv>                               (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ISeparateShaderObjects>               (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IParallelShaderCompile>               (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IClipControl>                         (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IConservativeRaster>                  (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ITextureView>                         (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ITextureBarrier>                      (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ITextureFilterAnisotropic>            (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ISparseTexture>                       (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IMeshShader>                          (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShadingRateImage>                    (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShaderSubGroup>                      (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShaderGroupVote>                     (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShaderInt64>                         (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IFragmentShaderInterlock>             (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IShaderViewportLayerArray>            (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IMemoryObject>                        (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ISemaphore>                           (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IDebug>                               (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ITimerQuery>                          (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IPipelineStatisticsQuery>             (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IGetProgramBinary>                    (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IRobustness>                          (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IES32Compatibility>                   (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IFragmentShaderBarycentric>           (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IInvalidateSubdata>                   (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IMultiBind>                           (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IQueryBufferObject>                   (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::ITimelineSemaphore>                   (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IVertexAttribBinding>                 (Capability::ECapabilityState::Extent);
		m_Context.Registry<Capability::IKeydMutex>                           (Capability::ECapabilityState::Extent);
    }

}

#endif