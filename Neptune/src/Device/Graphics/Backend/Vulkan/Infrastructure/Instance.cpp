/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Instance.h"
#include "Functions.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DebugUtils.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Portability.h"

namespace Neptune::Vulkan {

    Instance::Instance(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Instance::Create()
    {
		NEPTUNE_PROFILE_ZONE

    	if (!CheckExtensionRequirementsSatisfied())
    	{
    		NEPTUNE_LOG_CORE(E) << "Instance Extension not Satisfied";
    		return;
    	}
    	
    	GetLayerRequirements();
    	
    	if (!CheckLayerRequirementsSatisfied())
    	{
    		NEPTUNE_LOG_CORE(E) << "Instance Layer not Satisfied";
    		return;
    	}
    	
    	VkDebugUtilsMessengerCreateInfoEXT         debugInfo {};
    	debugInfo.sType                          = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    	debugInfo.messageSeverity                = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
									           	 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
									           	 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   
									           	 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
    	debugInfo.messageType                    = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT      
									           	 | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT   
									           	 | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    	debugInfo.pfnUserCallback                = DebugCallback;
    	debugInfo.pUserData                      = nullptr;
    	debugInfo.pNext                          = nullptr;
    	
        VkValidationFeaturesEXT					   validationFeatures{};

		if (const auto debugUtils = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IDebugUtils>())
		{
			validationFeatures.sType						    = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
			validationFeatures.enabledValidationFeatureCount    = static_cast<uint32_t>(debugUtils->GetFeatures().size());
			validationFeatures.pEnabledValidationFeatures       = debugUtils->GetFeatures().data();

			debugInfo.pNext                                     = &validationFeatures;
		}
    	
        VkApplicationInfo                          appInfo {};
		appInfo.sType                            = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName                 = "Neptune";
		appInfo.applicationVersion               = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName                      = "Neptune";
		appInfo.engineVersion                    = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion                       = VK_VERSION;

        VkInstanceCreateInfo                       createInfo {};
		createInfo.sType                         = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo              = &appInfo;
		createInfo.enabledExtensionCount         = static_cast<uint32_t>(m_ExtensionProperties.size());
		createInfo.ppEnabledExtensionNames       = m_ExtensionProperties.data();
		createInfo.enabledLayerCount             = static_cast<uint32_t>(m_LayerProperties.size());
		createInfo.ppEnabledLayerNames           = m_LayerProperties.data();
        createInfo.pNext                         = nullptr;

        if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDebugUtils>())
        {
		    createInfo.pNext                     = &debugInfo;
        }

    	if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IPortability>())
    	{
    		createInfo.flags                     = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    	}
    	
		m_Instance.CreateInstance(createInfo);

		GetContext().Registry<IFunctions>();

		GetContext().Get<IFunctions>()->Init(Handle());

        if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDebugUtils>())
        {
            m_DebugMessenger.SetFunctor(
                GetContext().Get<IFunctions>()->vkCreateDebugUtilsMessengerEXT,
                GetContext().Get<IFunctions>()->vkDestroyDebugUtilsMessengerEXT
            );

            m_DebugMessenger.CreateDebugUtilsMessenger(Handle(), debugInfo);
        }
    }

	bool Instance::CheckExtensionRequirementsSatisfied()
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t extensionCount = 0;
		VULKAN_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr))

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		VULKAN_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data()))
    	
    	bool coreSatisfied = true;
    	
    	std::vector<EExtension> removedExtension;
    	
    	GetContext().Get<IExtensions>()->GetContext().View([&](const auto e, const auto& extension) {
    		
    		bool satisfy = true;
    		const auto& extensions = extension->GetInstanceExtensions();
    		
            auto filtered = std::views::keys(extensions | std::views::filter([](const auto& pair) {
                return pair.second;
            }));
    		
    		std::ranges::for_each(filtered, [&](const auto& name) {
    			
    			std::string target(name);
    			
                if (std::ranges::all_of(availableExtensions, [&](const auto& ext) { return ext.extensionName != target; }))
    			{
                	if (extension->GetState() == Extension::EExtensionState::Core)
                	{
                		coreSatisfied = false;
                		
						NEPTUNE_LOG_CORE(E) << "Instance Extension Required: " << target << ", Which is not satisfied";
                	}
	                else
	                {
	                	NEPTUNE_LOG_CORE(W) << "Instance Extension Required: " << target << ", Which is not satisfied";
	                }

    				satisfy = false;
    			}
    		});
    		
    		if (satisfy)
    		{
    			m_ExtensionProperties.insert(m_ExtensionProperties.end(), filtered.begin(), filtered.end());
    		}
		    else
		    {
		    	removedExtension.emplace_back(e);
		    }
    	});
    	
    	std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
    		GetContext().Get<IExtensions>()->GetContext().UnRegistry(e);
    	});
    	
    	return coreSatisfied;
	}

	void Instance::GetLayerRequirements()
	{
		NEPTUNE_PROFILE_ZONE

    	if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDebugUtils>())
    	{
    		m_LayerProperties.push_back("VK_LAYER_KHRONOS_validation");
    	}
	}

	bool Instance::CheckLayerRequirementsSatisfied()
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t layerCount;
		VULKAN_CHECK(vkEnumerateInstanceLayerProperties(&layerCount, nullptr))

		std::vector<VkLayerProperties> availableLayers(layerCount);
		VULKAN_CHECK(vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data()))

		std::set<std::string> requiredLayers(m_LayerProperties.begin(), m_LayerProperties.end());

		for (const auto& layer : availableLayers) 
		{
			requiredLayers.erase(layer.layerName);
		}

		if (!requiredLayers.empty())
		{
			for (auto& set : requiredLayers)
			{
				NEPTUNE_LOG_CORE(W) << "Instance Layer Required: " << set << ", Which is not satisfied";
			}
		}

		return requiredLayers.empty();
	}

}

#endif