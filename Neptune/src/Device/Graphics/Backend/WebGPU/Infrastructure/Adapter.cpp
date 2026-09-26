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

        WGPURequestAdapterOptions              options{};
        options.powerPreference              = WGPUPowerPreference_HighPerformance;
        
        m_Adapter.CreateAdapter(GetContext().Get<IInstance>()->Handle(), options);
        
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
            << "    DeviceID:        " << info.deviceID;
        
        NEPTUNE_LOG_CORE(I) << ss.str();
        
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

    bool Adapter::CheckLimitRequirementsSatisfied()
    {
        NEPTUNE_PROFILE_ZONE

        WEBGPU_CHECK(wgpuAdapterGetLimits(m_Adapter.GetHandle(), &m_Limits))
        
        std::stringstream ss;

        ss << "Adapter Limit List: ";

        ss  << "    maxTextureDimension1D:                            " << m_Limits.maxTextureDimension1D << "\n"
            << "    maxTextureDimension2D:                            " << m_Limits.maxTextureDimension2D << "\n"
            << "    maxTextureDimension3D:                            " << m_Limits.maxTextureDimension3D << "\n"
            << "    maxTextureArrayLayers:                            " << m_Limits.maxTextureArrayLayers << "\n"
            << "    maxBindGroups:                                    " << m_Limits.maxBindGroups << "\n"
            << "    maxBindGroupsPlusVertexBuffers:                   " << m_Limits.maxBindGroupsPlusVertexBuffers << "\n"
            << "    maxBindingsPerBindGroup:                          " << m_Limits.maxBindingsPerBindGroup << "\n"
            << "    maxDynamicUniformBuffersPerPipelineLayout:        " << m_Limits.maxDynamicUniformBuffersPerPipelineLayout << "\n"
            << "    maxDynamicStorageBuffersPerPipelineLayout:        " << m_Limits.maxDynamicStorageBuffersPerPipelineLayout << "\n"
            << "    maxSampledTexturesPerShaderStage:                 " << m_Limits.maxSampledTexturesPerShaderStage << "\n"
            << "    maxSamplersPerShaderStage:                        " << m_Limits.maxSamplersPerShaderStage << "\n"
            << "    maxStorageBuffersPerShaderStage:                  " << m_Limits.maxStorageBuffersPerShaderStage << "\n"
            << "    maxUniformBuffersPerShaderStage:                  " << m_Limits.maxUniformBuffersPerShaderStage << "\n"
            << "    maxUniformBufferBindingSize:                      " << m_Limits.maxUniformBufferBindingSize << "\n"
            << "    maxStorageBufferBindingSize:                      " << m_Limits.maxStorageBufferBindingSize << "\n"
            << "    minUniformBufferOffsetAlignment:                  " << m_Limits.minUniformBufferOffsetAlignment << "\n"
            << "    minStorageBufferOffsetAlignment:                  " << m_Limits.minStorageBufferOffsetAlignment << "\n"
            << "    maxVertexBuffers:                                 " << m_Limits.maxVertexBuffers << "\n"
            << "    maxBufferSize:                                    " << m_Limits.maxBufferSize << "\n"
            << "    maxVertexAttributes:                              " << m_Limits.maxVertexAttributes << "\n"
            << "    maxVertexBufferArrayStride:                       " << m_Limits.maxVertexBufferArrayStride << "\n"
            << "    maxInterStageShaderVariables:                     " << m_Limits.maxInterStageShaderVariables << "\n"
            << "    maxColorAttachments:                              " << m_Limits.maxColorAttachments << "\n"
            << "    maxColorAttachmentBytesPerSample:                 " << m_Limits.maxColorAttachmentBytesPerSample << "\n"
            << "    maxComputeWorkgroupStorageSize:                   " << m_Limits.maxComputeWorkgroupStorageSize << "\n"
            << "    maxComputeInvocationsPerWorkgroup:                " << m_Limits.maxComputeInvocationsPerWorkgroup << "\n"
            << "    maxComputeWorkgroupSizeX:                         " << m_Limits.maxComputeWorkgroupSizeX << "\n"
            << "    maxComputeWorkgroupSizeY:                         " << m_Limits.maxComputeWorkgroupSizeY << "\n"
            << "    maxComputeWorkgroupSizeZ:                         " << m_Limits.maxComputeWorkgroupSizeZ << "\n"
            << "    maxComputeWorkgroupsPerDimension:                 " << m_Limits.maxComputeWorkgroupsPerDimension << "\n"
            << "    maxImmediateSize:                                 " << m_Limits.maxImmediateSize;

        NEPTUNE_LOG_CORE(I) << ss.str();

        return true;
    }

}

#endif