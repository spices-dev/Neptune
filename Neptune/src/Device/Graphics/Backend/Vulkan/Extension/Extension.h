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
        
    private:
        
        std::unordered_map<const char*, bool> m_InstanceExtensions;      // @brief VkInstance Extensions.
        std::unordered_map<const char*, bool> m_DeviceExtensions;        // @brief VkPhysicalDevice/VkDevice Extensions.
        std::unordered_set<VkStructureType>   m_DeviceFeatures;          // @brief VkPhysicalDevice/VkDevice Features.
        bool                                  m_Valid;                   // @brief This Extension Valid;
    };
}

#endif