/**
* @file Extension.h.
* @brief The Extension Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"

namespace Neptune::Vulkan::Extension {
    
    /**
    * @brief Vulkan::Extension Class.
    * This class defines the Vulkan::Extension behaves.
    */
    class Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Extension() = default;
        
        /**
        * @brief Destructor Function.
        */
        virtual ~Extension() = default;

        /**
        * @brief Add VkInstance Extension Requirement.
        * 
        * @param[in] name Extension Name.
        * @param[in] value On/Off.
        */
        void AddInstanceExtensions(const char* name, bool value = true);
        
        /**
        * @brief Add VkPhysicalDevice/VkDevice Extension Requirement.
        * 
        * @param[in] name Extension Name.
        * @param[in] value On/Off.
        */
        void AddDeviceExtensions(const char* name, bool value = true);
        
        /**
        * @brief Add VkPhysicalDevice/VkDevice Features Requirement.
        * 
        * @param[in] type Features Type.
        */
        void AddDeviceFeatures(VkStructureType type);
        
        /**
        * @brief Get VkInstance Extension Requirement.
        * 
        * @return Returns VkInstance Extension Requirement.
        */
        const std::unordered_map<const char*, bool>& GetInstanceExtensions() const { return m_InstanceExtensions; }
        
        /**
        * @brief Get VkPhysicalDevice/VkDevice Extension Requirement.
        * 
        * @return Returns VkPhysicalDevice/VkDevice Extension Requirement.
        */
        const std::unordered_map<const char*, bool>& GetDeviceExtensions() const { return m_DeviceExtensions; }

        /**
        * @brief Build Device Feature Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        virtual void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) {}

        /**
        * @brief Combine Device Features.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsFeaturesSatisfied() { return true; }
        
    private:
        
        std::unordered_map<const char*, bool> m_InstanceExtensions;      // @brief VkInstance Extensions.
        std::unordered_map<const char*, bool> m_DeviceExtensions;        // @brief VkPhysicalDevice/VkDevice Extensions.
        std::unordered_set<VkStructureType>   m_DeviceFeatures;          // @brief VkPhysicalDevice/VkDevice Features.
    };
}

#endif