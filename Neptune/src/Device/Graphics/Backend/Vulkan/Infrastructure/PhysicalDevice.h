/**
* @file PhysicalDevice.h.
* @brief The PhysicalDevice Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/PhysicalDevice.h"
#include "Core/Container/LinkedUnorderedMap.h"

#include <vector>
#include <optional>

namespace Neptune::Vulkan {

	/**
	* @brief SwapChain Property.
	*/
	struct SwapChainProperty
	{
		VkSurfaceCapabilitiesKHR        capabilities;                           // @brief VkSurfaceCapabilitiesKHR.
		std::vector<VkSurfaceFormatKHR> formats;                                // @brief VkSurfaceFormatKHR.
		std::vector<VkPresentModeKHR>   presentModes;                           // @brief VkPresentModeKHR.
		VkSurfaceFormatKHR              format;                                 // @brief VkSurfaceFormatKHR.
		VkPresentModeKHR                presentMode;                            // @brief VkPresentModeKHR.
		VkExtent2D                      surfaceSize = {0, 0};      // @brief VkExtent2D.
	};

	/**
	* @brief VideoSession Property.
	*/
	struct VideoSessionProperty
	{
		VkVideoCapabilitiesKHR          capabilities;       // @brief VkVideoCapabilitiesKHR.
		VkFormat                        dpbFormat;          // @brief VkFormat.
		VkFormat                        dstFormat;          // @brief VkFormat.
	};

	using IPhysicalDevice = IInfrastructure<class PhysicalDevice, EInfrastructure::PhysicalDevice>;

	/**
	* @brief Vulkan::PhysicalDevice Class.
	* This class defines the Vulkan::PhysicalDevice behaves.
	*/
	class PhysicalDevice : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		PhysicalDevice(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~PhysicalDevice() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::PhysicalDevice::Handle& Handle() const { return m_PhysicalDevice.GetHandle(); }

		/**
		* @brief Get Extensions.
		*
		* @return Returns Extensions.
		*/
		std::vector<const char*> GetExtensionRequirements() const;

		/**
		* @brief Get Properties.
		*
		* @return Returns Properties.
		*/
		const VkPhysicalDeviceProperties& GetProperties() const { return m_Properties; }

		/**
		* @brief Get SwapChain Properties.
		*
		* @return Returns SwapChain Properties.
		*/
		const SwapChainProperty& GetSwapChainProperty() { return m_SwapChainProperty; }

		/**
		* @brief Get VideoSession Properties.
		*
		* @return Returns VideoSession Properties.
		*/
		VideoSessionProperty QueryVideoSessionProperty(const VkVideoProfileInfoKHR& videoProfile);

		/**
		* @brief Is OpticalFlow Session Support.
		*
		* @param[in] inputFormat VkFormat.
		* @param[in] outFormat VkFormat.
		* 
		* @return Returns true if supported.
		*/
		bool IsOpticalFlowSessionSupport(VkFormat inputFormat, VkFormat outFormat);

		/**
		* @brief Query SwapChain Property.
		*
		* @return Returns SwapChain Property.
		*/
		const SwapChainProperty& QuerySwapChainProperty();

	private:

		/**
		* @brief Create Instance.
		*/
		void Create();

		/**
		* @brief Device Detection.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns Extensions.
		*/
		SP<class Extensions> DeviceDetection(const VkPhysicalDevice& device) const;
		
		/**
		* @brief Select Best PhysicalDevice.
		* 
		* @param[in] devices VkPhysicalDevice.
		* 
		* @return Returns best VkPhysicalDevice.
		*/
		VkPhysicalDevice SelectBestDevice(const std::vector<VkPhysicalDevice>& devices) const;
		
		/**
		* @brief Properties Query.
		*/
		void PropertiesQuery();
		
		/**
		* @brief Is Extension Meet Demand.
		* 
		* @param[in] extensions Extensions.
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if meets.
		*/
		bool IsExtensionMeetDemand(class Extensions* extensions, const VkPhysicalDevice& device) const;

		/**
		* @brief Is Property Meet Demand.
		*
		* @param[in] extensions Extensions.
		* @param[in] device VkPhysicalDevice.
		*
		* @return Returns true if meets.
		*/
		bool IsPropertyMeetDemand(class Extensions* extensions, const VkPhysicalDevice& device) const;

		/**
		* @brief Is Feature Meet Demand.
		*
		* @param[in] extensions Extensions.
		* @param[in] device VkPhysicalDevice.
		*
		* @return Returns true if meets.
		*/
		bool IsFeatureMeetDemand(class Extensions* extensions, const VkPhysicalDevice& device) const;

		/**
		* @brief Is Surface Capability Meet Demand.
		*
		* @param[in] extensions Extensions.
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		*
		* @return Returns true if meets.
		*/
		bool IsSurfaceCapabilityMeetDemand(class Extensions* extensions, const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const;
		
		/**
		* @brief Is Queue Meet Demand.
		*
		* @param[in] extensions Extensions.
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		*
		* @return Returns true if meets.
		*/
		bool IsQueueMeetDemand(class Extensions* extensions, const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const;

		/**
		* @brief Is Surface Format Meet Demand.
		*
		* @param[in] extensions Extensions.
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		*
		* @return Returns true if meets.
		*/
		bool IsSurfaceFormatMeetDemand(class Extensions* extensions, const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const;
		
		/**
		* @brief Is Queue OpticalFlow Session Supported.
		*
		* @param[in] inputformat VkFormat.
		* @param[in] usage VkOpticalFlowUsageFlagsNV.
		*
		* @return Returns true if supported.
		*/
		bool IsOpticalFlowSessionSupport(VkFormat inputformat, VkOpticalFlowUsageFlagsNV usage);

		/**
		* @brief Get Video supported formats.
		*
		* @param[in] imageUsage VkImageUsageFlags.
		* @param[in] videoProfile VkVideoProfileInfoKHR.
		*
		* @return Returns supported formats.
		*/
		std::vector<VkFormat> GetVideoFormats(VkImageUsageFlags imageUsage, const std::vector<VkVideoProfileInfoKHR>& videoProfile);

	private:

		Unit::PhysicalDevice        m_PhysicalDevice;              // @brief This PhysicalDevice.
		VkPhysicalDeviceProperties  m_Properties;                  // @brief VkPhysicalDeviceProperties.
		SwapChainProperty           m_SwapChainProperty;           // @brief SwapChainProperty.
	};

}

#endif