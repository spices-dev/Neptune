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
        
    	m_ApiVersion = major * 10 + minor;
    	
    	m_ApiVersion = std::min(m_ApiVersion, OPENGL_DEV_VERSION);
		
    	Extension::Extension::SetApiVersion(m_ApiVersion);
    	
    	Registry();

    	if (!IsExtensionMeetDemand())
    	{
    		NEPTUNE_LOG_CORE(C) << "OpenGL Core Extension is not satisfied.";

    		NEPTUNE_BREAK
		}
        
    	if (!IsPropertyMeetDemand())
    	{
    		NEPTUNE_LOG_CORE(C) << "OpenGL Core Extension Property is not satisfied.";

    		NEPTUNE_BREAK
    	}
    }

	void Extensions::Registry()
    {
    	NEPTUNE_PROFILE_ZONE
    	
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
	
	bool Extensions::IsExtensionMeetDemand()
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	GLint count = 0;
        
    	glGetIntegerv(GL_NUM_EXTENSIONS, &count);
        
    	std::vector<const char*> availableExtensions;
    	
    	for (GLint i = 0; i < count; ++i)
    	{
    		const auto* name = glGetStringi(GL_EXTENSIONS, static_cast<GLuint>(i));
            
    		if (!name) continue;
            
    		availableExtensions.emplace_back(reinterpret_cast<const char*>(name));
    	}

    	bool coreSatisfied = true;
    	
    	std::vector<EExtension> removedExtension;
    	
    	m_Context.View([&](const auto e, const auto& extension) {
    		
			bool satisfy = true;
			const auto& extensions = extension->GetExtensions();
    		
			auto filtered = std::views::keys(extensions | std::views::filter([](const auto& pair) {
				return pair.second;
			}));
    		
			std::ranges::for_each(filtered, [&](const auto& name) {
    			
				std::string target(name);
    			
				if (std::ranges::all_of(availableExtensions, [&](const auto& ext) { return std::string(ext) != target; }))
				{
					if (extension->GetState() == Extension::EExtensionState::Core)
					{
						coreSatisfied = false;
                		
						NEPTUNE_LOG_CORE(E) << "Extension Required: [ " << target << " ], Which is not satisfied";
					}
					else
					{
						NEPTUNE_LOG_CORE(W) << "Extension Required: [ " << target << " ], Which is not satisfied";
					}

					satisfy = false;
				}
			});
    		
			if (satisfy)
			{
				m_Extensions.insert(m_Extensions.end(), filtered.begin(), filtered.end());
			}
			else
			{
				removedExtension.emplace_back(e);
			}
		});
    	
    	std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			m_Context.UnRegistry(e);
		});
    	
    	return coreSatisfied;
    }
	
	bool Extensions::IsPropertyMeetDemand()
    {
    	NEPTUNE_PROFILE_ZONE

    	bool coreSatisfied = true;
		
    	std::vector<EExtension> removedExtension;
		
    	m_Context.View([&](const auto e, const auto& extension) {
			
    		extension->QueryProperties();
    		
			if (!extension->IsPropertiesSatisfied())
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;
					
					NEPTUNE_LOG_CORE(E) << "Extension Property Required: " << OpenGL::ToString(e) << ", Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Extension Property Required: " << OpenGL::ToString(e) << ", Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
    	std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			m_Context.UnRegistry(e);
		});
		
    	return coreSatisfied;
    }
	
	const char* Extensions::GetApiVersionName() const
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	if (m_ApiVersion == 46) return "#version 460";
    	if (m_ApiVersion == 45) return "#version 450";
    	if (m_ApiVersion == 44) return "#version 440";
    	if (m_ApiVersion == 43) return "#version 430";
    	if (m_ApiVersion == 42) return "#version 420";
    	if (m_ApiVersion == 41) return "#version 410";
    	if (m_ApiVersion == 40) return "#version 400";
    	
    	if (m_ApiVersion == 39) return "#version 390";
    	if (m_ApiVersion == 38) return "#version 380";
    	if (m_ApiVersion == 37) return "#version 370";
    	if (m_ApiVersion == 36) return "#version 360";
    	if (m_ApiVersion == 35) return "#version 350";
    	if (m_ApiVersion == 34) return "#version 340";
    	if (m_ApiVersion == 33) return "#version 330";
    	if (m_ApiVersion == 32) return "#version 320";
    	if (m_ApiVersion == 31) return "#version 310";
    	if (m_ApiVersion == 30) return "#version 300";
    	
    	if (m_ApiVersion == 29) return "#version 290";
    	if (m_ApiVersion == 28) return "#version 280";
    	if (m_ApiVersion == 27) return "#version 270";
    	if (m_ApiVersion == 26) return "#version 260";
    	if (m_ApiVersion == 25) return "#version 250";
    	if (m_ApiVersion == 24) return "#version 240";
    	if (m_ApiVersion == 23) return "#version 230";
    	if (m_ApiVersion == 22) return "#version 220";
    	if (m_ApiVersion == 21) return "#version 210";
    	if (m_ApiVersion == 20) return "#version 200";
    	
    	if (m_ApiVersion == 19) return "#version 190";
    	if (m_ApiVersion == 18) return "#version 180";
    	if (m_ApiVersion == 17) return "#version 170";
    	if (m_ApiVersion == 16) return "#version 160";
    	if (m_ApiVersion == 15) return "#version 150";
    	if (m_ApiVersion == 14) return "#version 140";
    	if (m_ApiVersion == 13) return "#version 130";
    	if (m_ApiVersion == 12) return "#version 120";
    	if (m_ApiVersion == 11) return "#version 110";
    	if (m_ApiVersion == 10) return "#version 100";
    	
    	NEPTUNE_BREAK
    	
    	return OPENGL_DEV_VERSION_NAME;
    }
}

#endif