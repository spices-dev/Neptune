/**
* @file Adapter.cpp.
* @brief The Adapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "Instance.h"
#include "DebugUtilsObject.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/WebGPU/Converter.h"

namespace Neptune::WebGPU {

    Adapter::Adapter(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Adapter::Create()
    {
        NEPTUNE_PROFILE_ZONE

        if (!CheckFeatureRequirementsSatisfied())
        {
            NEPTUNE_LOG_CORE(E) << "Adapter Feature not Satisfied";
            return;
        }
        
        if (!CheckLimitRequirementsSatisfied())
        {
            NEPTUNE_LOG_CORE(E) << "Adapter Limit not Satisfied";
            return;
        }
        
        m_Adapter.CreateAdapter(GetContext().Get<IInstance>()->Handle());
        
        DEBUGUTILS_SETOBJECTNAME(m_Adapter, ToString())
        
        WGPUAdapterInfo info{};

        WEBGPU_CHECK(wgpuAdapterGetInfo(m_Adapter.GetHandle(), &info))
        
        std::stringstream ss;
		
        ss << "Adapter List: ";
			
        ss <<"\n" << "Device [ " << 0 << " ]: " << "\n"
            << "    Name:            " << info.device.data << "\n"
            << "    Description:     " << info.description.data << "\n"
            << "    Architecture:    " << info.architecture.data << "\n"
            << "    Vendor:          " << info.vendor.data << "\n"
            << "    Type:            " << WebGPU::ToString(info.adapterType) << "\n"
            << "    Backend:         " << WebGPU::ToString(info.backendType) << "\n"
            << "    VendorID:        " << info.vendorID << "\n"
            << "    DeviceID:        " << info.deviceID << "\n";
        
        NEPTUNE_LOG_CORE(I) << ss.str();
    }

    bool Adapter::CheckFeatureRequirementsSatisfied()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedFeatures features{};

        wgpuAdapterGetFeatures(m_Adapter.GetHandle(), &features);
        
        std::vector<WGPUFeatureName> availableFeatures(features.featureCount);
        
        std::memcpy(availableFeatures.data(), features.features, features.featureCount * sizeof(WGPUInstanceFeatureName));
        
        bool coreSatisfied = true;
    	
        std::vector<EExtension> removedExtension;
    	
        GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
    		
            bool satisfy = true;
            const auto& extensions = extension->GetAdapterFeatures();
    		
            auto filtered = std::views::keys(extensions | std::views::filter([](const auto& pair) {
                return pair.second;
            }));
    		
            std::ranges::for_each(filtered, [&](const auto& name) {
    			
                if (std::ranges::all_of(availableFeatures, [&](const auto& ext) { return ext != name; }))
                {
                    if (extension->GetState() == Extension::EExtensionState::Core)
                    {
                        coreSatisfied = false;
                		
                        NEPTUNE_LOG_CORE(E) << "Adapter Feature Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
                    }
                    else
                    {
                        NEPTUNE_LOG_CORE(W) << "Adapter Feature Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
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

    bool Adapter::CheckLimitRequirementsSatisfied()
    {
        NEPTUNE_PROFILE_ZONE

        WGPULimits limit{};

        WEBGPU_CHECK(wgpuAdapterGetLimits(m_Adapter.GetHandle(), &limit))
        
        bool coreSatisfied = true;
    	
        std::vector<EExtension> removedExtension;
    	
        GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
    		
            if (extension->IsAdapterLimitsSatisfied(limit)) return;
            
            if (extension->GetState() == Extension::EExtensionState::Core)
            {
                coreSatisfied = false;

                NEPTUNE_LOG_CORE(E) << "Adapter Limit Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
            }
            else
            {
                NEPTUNE_LOG_CORE(W) << "Adapter Limit Required: [ " << WebGPU::ToString(e) << " ], Which is not satisfied";
            }
            
            removedExtension.emplace_back(e);
        });
    	
        std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
            GetContext().Get<IExtensions>()->GetContext()->UnRegistry(e);
        });
    	
        return coreSatisfied;
    }

}

#endif