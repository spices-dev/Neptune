/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Instance.h"
#include "DebugUtilsObject.h"
#include "Extensions.h"

namespace Neptune::WebGPU {

    Instance::Instance(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Instance::Create()
    {
        NEPTUNE_PROFILE_ZONE

        if (!CheckFeatureRequirementsSatisfied())
        {
            NEPTUNE_LOG_CORE(E) << "Instance Feature not Satisfied";
            return;
        }
        
        if (!CheckLimitRequirementsSatisfied())
        {
            NEPTUNE_LOG_CORE(E) << "Instance Limit not Satisfied";
            return;
        }
        
        if (!CheckWGSLFeatureRequirementsSatisfied())
        {
            NEPTUNE_LOG_CORE(E) << "WGSL Feature not Satisfied";
            return;
        }

        WGPUInstanceDescriptor                 descriptor{};
        descriptor.requiredFeatureCount      = m_Features.size();
        descriptor.requiredFeatures          = m_Features.data();

        m_Instance.CreateInstance(descriptor);
        
        DEBUGUTILS_SETOBJECTNAME(m_Instance, ToString())
    }

    void Instance::ProcessEvents() const
    {
        NEPTUNE_PROFILE_ZONE

        wgpuInstanceProcessEvents(m_Instance.GetHandle());
    }
    
    bool Instance::CheckFeatureRequirementsSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        WGPUSupportedInstanceFeatures features;

        wgpuGetInstanceFeatures(&features);
        
        std::vector<WGPUInstanceFeatureName> availableFeatures(features.featureCount);
        
        std::memcpy(availableFeatures.data(), features.features, features.featureCount * sizeof(WGPUInstanceFeatureName));
        
        bool coreSatisfied = true;
    	
        std::vector<EExtension> removedExtension;
    	
        GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
    		
            bool satisfy = true;
            const auto& extensions = extension->GetInstanceFeatures();
    		
            auto filtered = std::views::keys(extensions | std::views::filter([](const auto& pair) {
                return pair.second;
            }));
    		
            std::ranges::for_each(filtered, [&](const auto& name) {
    			
                if (std::ranges::all_of(availableFeatures, [&](const auto& ext) { return ext != name; }))
                {
                    if (extension->GetState() == Extension::EExtensionState::Core)
                    {
                        coreSatisfied = false;
                		
                        NEPTUNE_LOG_CORE(E) << "Instance Feature Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
                    }
                    else
                    {
                        NEPTUNE_LOG_CORE(W) << "Instance Feature Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
                    }

                    satisfy = false;
                }
            });
    		
            if (satisfy)
            {
                std::ranges::for_each(filtered, [&](const auto& name) { m_Features.emplace_back(name); });
            }
            else
            {
                removedExtension.emplace_back(e);
            }
        });
    	
        std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
            GetContext().Get<IExtensions>()->GetContext()->UnRegistry(e);
        });
    	
        return coreSatisfied;
    }
    
    bool Instance::CheckLimitRequirementsSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        WGPUInstanceLimits limit;

        WEBGPU_CHECK(wgpuGetInstanceLimits(&limit))
        
        bool coreSatisfied = true;
    	
        std::vector<EExtension> removedExtension;
    	
        GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
    		
            if (extension->IsInstanceLimitsSatisfied(limit)) return;
            
            if (extension->GetState() == Extension::EExtensionState::Core)
            {
                coreSatisfied = false;
                		
                NEPTUNE_LOG_CORE(E) << "Instance Limit Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
            }
            else
            {
                NEPTUNE_LOG_CORE(W) << "Instance Limit Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
            }
            
            removedExtension.emplace_back(e);
        });
    	
        std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
            GetContext().Get<IExtensions>()->GetContext()->UnRegistry(e);
        });
    	
        return coreSatisfied;
    }
    
    bool Instance::CheckWGSLFeatureRequirementsSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        WGPUSupportedWGSLLanguageFeatures features{};

        wgpuInstanceGetWGSLLanguageFeatures(m_Instance.GetHandle(), &features);
        
        std::vector<WGPUWGSLLanguageFeatureName> availableFeatures(features.featureCount);
        
        std::memcpy(availableFeatures.data(), features.features, features.featureCount * sizeof(WGPUWGSLLanguageFeatureName));
        
        bool coreSatisfied = true;
    	
        std::vector<EExtension> removedExtension;
    	
        GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
    		
            bool satisfy = true;
            const auto& extensions = extension->GetWGSLFeatures();
    		
            auto filtered = std::views::keys(extensions | std::views::filter([](const auto& pair) {
                return pair.second;
            }));
    		
            std::ranges::for_each(filtered, [&](const auto& name) {
    			
                if (std::ranges::all_of(availableFeatures, [&](const auto& ext) { return ext != name; }))
                {
                    if (extension->GetState() == Extension::EExtensionState::Core)
                    {
                        coreSatisfied = false;
                		
                        NEPTUNE_LOG_CORE(E) << "WGSL Feature Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
                    }
                    else
                    {
                        NEPTUNE_LOG_CORE(W) << "WGSL Feature Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
                    }

                    satisfy = false;
                }
            });
    		
            if (!satisfy)
            {
                removedExtension.emplace_back(e);
            }
        });
    	
        std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
            GetContext().Get<IExtensions>()->GetContext()->UnRegistry(e);
        });
    	
        return coreSatisfied;
    }

}

#endif