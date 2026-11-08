/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Core.h"
#include "Converter.h"

#include <vulkan/vk_enum_string_helper.h>

namespace Neptune::Vulkan {

	namespace {
	
        HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.

        /**
	 	* @brief Handle Device Lost Result.
	 	* 
	 	* @param device VkDevice.
	 	* @param ss DebugInfoStringStream.
	 	*/
        void HandleDeviceLostResult(VkDevice device, std::stringstream& ss)
		{
        	NEPTUNE_PROFILE_ZONE

        	VkDeviceFaultCountsEXT faultCount = { VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT };
        	
        	VkResult result = vkGetDeviceFaultInfoEXT(device, &faultCount, nullptr);

            if (result != VK_SUCCESS) 
            {
                NEPTUNE_LOG_CORE(E) << "Device Lost: Failed to Query Fault Counts.";
                return;
            }

        	if (faultCount.addressInfoCount == 0 && faultCount.vendorInfoCount == 0)
        	{
        		NEPTUNE_LOG_CORE(W) << "Device Lost: Nothing Report.";
        		return;
        	}

        	std::vector<VkDeviceFaultAddressInfoEXT> addressInfos(faultCount.addressInfoCount);
        	std::vector<VkDeviceFaultVendorInfoEXT> vendorInfos(faultCount.vendorInfoCount);
        	std::vector<char> vendorBinaryData(faultCount.vendorBinarySize);

        	VkDeviceFaultInfoEXT faultInfo = { VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT };

        	faultInfo.pAddressInfos     = addressInfos.data();
        	faultInfo.pVendorInfos      = vendorInfos.data();
        	faultInfo.pVendorBinaryData = vendorBinaryData.data();

        	result = vkGetDeviceFaultInfoEXT(device, &faultCount, &faultInfo);
        	
        	if (result != VK_SUCCESS) return;

        	std::stringstream info;
        		
        	info << "\n" << "Description: " << faultInfo.description << "\n";
        	info << "    Vendor: description = " << (faultInfo.pVendorInfos ? faultInfo.pVendorInfos->description : "No Vendor Information available.");
        	
			for (uint32_t i = 0; i < faultCount.addressInfoCount; i++) {
				
				uint64_t lower = addressInfos[i].reportedAddress & ~(addressInfos[i].addressPrecision - 1);
				uint64_t upper = addressInfos[i].reportedAddress | (addressInfos[i].addressPrecision - 1);
				
				info << "    Address: type = " << string_VkDeviceFaultAddressTypeKHR(addressInfos[i].addressType) << ", reported = " << addressInfos[i].reportedAddress << ", precision = " << addressInfos[i].addressPrecision
				   << "\n" << "    Address range :" << lower << " - " << upper << "\n";
			}
        	
        	ss << info.str();
        	
            NEPTUNE_LOG_CORE(E) << ss.str();
		}
		
		/**
		 * @brief Handle Memory Budget Result.
		 * 
		 * @param physicalDevice VkPhysicalDevice.
		 * @param ss DebugInfoStringStream.
		 */
		void HandleMemoryBudgetResult(VkPhysicalDevice physicalDevice, std::stringstream& ss)
        {
        	NEPTUNE_PROFILE_ZONE
        	
        	VkPhysicalDeviceMemoryBudgetPropertiesEXT      memoryBudgetProperties{};
        	memoryBudgetProperties.sType                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
        	memoryBudgetProperties.pNext                 = nullptr;

        	VkPhysicalDeviceMemoryProperties2              memoryProperties{};
        	memoryProperties.sType                       = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
        	memoryProperties.pNext                       = &memoryBudgetProperties;

        	vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memoryProperties);

        	ss << "\n";

        	for (uint64_t i = 0; i < memoryProperties.memoryProperties.memoryHeapCount; i++)
        	{
        		ss << "                        Heap: [ " << ToString(memoryProperties.memoryProperties.memoryHeaps[i].flags) << " ] Budget: [ " << memoryBudgetProperties.heapBudget[i] << " ] Usage: [ " << memoryBudgetProperties.heapUsage[i] << " ]\n";
        	}

        	NEPTUNE_LOG_CORE(E) << ss.str();
        }
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL InstanceDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT         messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT                messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT*    pCallbackData, 
		void*                                          pUserData
	) {
		NEPTUNE_PROFILE_ZONE

		std::stringstream ss;

		ss <<
		"Vulkan Validation layer:\n			" <<
		"MessageIdNumber: " <<
		pCallbackData->messageIdNumber <<
		"\n			MessageIdName: " <<
		pCallbackData->pMessageIdName;

		if (pCallbackData->cmdBufLabelCount != 0)
		{
			ss << "\n		CmdLabelName: ";

			for (int i = 0; i < pCallbackData->cmdBufLabelCount; ++i)
			{
				ss << "[" << pCallbackData->pCmdBufLabels[i].pLabelName << "] ";
			}
		}

		ss <<
		"\n			Message: " <<
		pCallbackData->pMessage;

		switch (messageSeverity)
		{
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			{
				NEPTUNE_LOG_CORE(T) << ss.str();
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			{
				NEPTUNE_LOG_CORE(I) << ss.str();
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			{
				NEPTUNE_LOG_CORE(W) << ss.str();
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			{
				NEPTUNE_LOG_CORE(E) << ss.str();
				break;
			}
			default:
			{
				NEPTUNE_LOG_CORE(I) << ss.str();
				break;
			}
		}

		return VK_FALSE;
	}
	
	VKAPI_ATTR VkBool32 VKAPI_CALL DeviceDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT         messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT                messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT*    pCallbackData, 
		void*                                          pUserData
	) {
		NEPTUNE_PROFILE_ZONE
		
		if (auto* bindingData = static_cast<const VkDeviceAddressBindingCallbackDataEXT*>(pCallbackData->pNext))
		{
			std::stringstream ss;
			
			ss << "\n " << "Objects: \n";
			
			if (bindingData->sType == VK_STRUCTURE_TYPE_DEVICE_ADDRESS_BINDING_CALLBACK_DATA_EXT)
			{
				for (uint32_t i = 0; i < pCallbackData->objectCount; ++i) {
					const auto& obj = pCallbackData->pObjects[i];
					ss << "    ObjectType: " << obj.objectType << ", ObjectHandle: " << obj.objectHandle << ", ObjectName: " << (obj.pObjectName ? obj.pObjectName : "NonNamed") << "\n";
				}
				
				switch (bindingData->bindingType) {
				case VK_DEVICE_ADDRESS_BINDING_TYPE_BIND_EXT:
					ss << "Address Bound -> Decimal: " << bindingData->baseAddress << " | Hex: 0x" << bindingData->baseAddress << " | Size = " << bindingData->size << " Bytes";
					break;

				case VK_DEVICE_ADDRESS_BINDING_TYPE_UNBIND_EXT:
					ss << "Address Unbound -> Decimal: " << bindingData->baseAddress << " | Hex: 0x" << bindingData->baseAddress << " | Size = " << bindingData->size << " Bytes";
					break;
				}
			}
			
			switch (messageSeverity)
			{
				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				{
					NEPTUNE_LOG_CORE(T) << ss.str();
					break;
				}
				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				{
					NEPTUNE_LOG_CORE(I) << ss.str();
					break;
				}
				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				{
					NEPTUNE_LOG_CORE(W) << ss.str();
					break;
				}
				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				{
					NEPTUNE_LOG_CORE(E) << ss.str();
					break;
				}
				default:
				{
					NEPTUNE_LOG_CORE(I) << ss.str();
					break;
				}
			}
		}
		
		return VK_FALSE;
	}
	
	void HandleResult(VkResult result, VkPhysicalDevice physicalDevice, VkDevice device, bool deviceFaultValid, bool memoryBudget)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == VK_SUCCESS) return;

		std::stringstream ss;
		ss << "Vulkan Error: [ " << string_VkResult(result) << " ]";

		if (result == VK_ERROR_DEVICE_LOST && device && deviceFaultValid)
		{
			HandleDeviceLostResult(device, ss);
		}

        if ((result == VK_ERROR_OUT_OF_HOST_MEMORY || result == VK_ERROR_OUT_OF_DEVICE_MEMORY) && physicalDevice && memoryBudget)
        {
        	HandleMemoryBudgetResult(physicalDevice, ss);
        }

        NEPTUNE_LOG_CORE(E) << ss.str();
	}
}

#endif