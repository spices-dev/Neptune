/**
* @file DebugUtilsMessenger.h.
* @brief The DebugUtilsMessenger Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::DebugUtilsMessenger Class.
    * This class defines the Vulkan::Unit::DebugUtilsMessenger behaves.
    */
    class DebugUtilsMessenger : public Unit<VkDebugUtilsMessengerEXT, VkObjectType::VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DebugUtilsMessenger() = default;

        /**
        * @brief Destructor Function.
        */
        ~DebugUtilsMessenger() override;

        /**
        * @brief Set Functor.
        * 
        * @param[in] create PFN_vkCreateDebugUtilsMessengerEXT.
        * @param[in] destroy PFN_vkDestroyDebugUtilsMessengerEXT.
        */
        void SetFunctor(PFN_vkCreateDebugUtilsMessengerEXT create, PFN_vkDestroyDebugUtilsMessengerEXT destroy);
        
        /**
        * @brief Create DebugUtilsMessenger.
        *
        * @param[in] instance VkInstance.
        * @param[in] info VkDebugUtilsMessengerCreateInfoEXT.
        */
        void CreateDebugUtilsMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT& info);

    private:

        VkInstance                            m_Instance = VK_NULL_HANDLE;       // @brief VkInstance.
        PFN_vkCreateDebugUtilsMessengerEXT    vkCreateDebugUtilsMessengerEXT;    // @brief PFN_vkCreateDebugUtilsMessengerEXT
        PFN_vkDestroyDebugUtilsMessengerEXT   vkDestroyDebugUtilsMessengerEXT;   // @brief PFN_vkDestroyDebugUtilsMessengerEXT
    };
}

#endif