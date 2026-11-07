/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Instance Class.
    * This class defines the Vulkan::Unit::Instance behaves.
    */
    class Instance : public Unit<VkInstance, PFN_vkCreateInstance, PFN_vkDestroyInstance>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Instance() = default;

        /**
        * @brief Destructor Function.
        */
        ~Instance() override;
        
        /**
        * @brief Create Instance.
        *
        * @param[in] info VkInstanceCreateInfo.
        * 
        * @return Returns VkResult.
        */
        VkResult CreateInstance(const VkInstanceCreateInfo& info);
    };
}