/**
* @file Extensions.cpp.
* @brief The Extensions Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Extensions.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ExtensionHeader.h"

namespace Neptune::OpenGL {

    Extensions::Extensions(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Extensions::Create()
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
        
        m_Context.Registry<Extension::IDirectStateAccess>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IBufferStorage>                       (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IComputeShader>                       (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IMultiDrawIndirect>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IIndirectParameters>                  (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShaderDrawParameters>                (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShaderStorageBufferObject>           (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IBindlessTexture>                     (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ISpirv>                               (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ISeparateShaderObjects>               (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IParallelShaderCompile>               (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IClipControl>                         (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IConservativeRaster>                  (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ITextureView>                         (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ITextureBarrier>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ITextureFilterAnisotropic>            (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ISparseTexture>                       (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IMeshShader>                          (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShadingRateImage>                    (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShaderSubGroup>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShaderGroupVote>                     (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShaderInt64>                         (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IFragmentShaderInterlock>             (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IShaderViewportLayerArray>            (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IMemoryObject>                        (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ISemaphore>                           (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDebug>                               (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ITimerQuery>                          (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IPipelineStatisticsQuery>             (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IGetProgramBinary>                    (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IRobustness>                          (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IES32Compatibility>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IFragmentShaderBarycentric>           (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IInvalidateSubdata>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IMultiBind>                           (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IQueryBufferObject>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ITimelineSemaphore>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IVertexAttribBinding>                 (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IKeydMutex>                           (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IViewportLayerArray>                  (Extension::EExtensionState::Extent);
    }

}

#endif