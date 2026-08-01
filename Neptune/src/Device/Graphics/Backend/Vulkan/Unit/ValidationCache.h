/**
* @file ValidationCache.h.
* @brief The ValidationCache Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::ValidationCache Class.
    * This class defines the Vulkan::Unit::ValidationCache behaves.
    */
    class ValidationCache : public Unit<VkValidationCacheEXT, VkObjectType::VK_OBJECT_TYPE_VALIDATION_CACHE_EXT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ValidationCache() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~ValidationCache() override;

        /**
        * @brief Create ValidationCache.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkPrivateDataSlotCreateInfo.
        */
        void CreateValidationCache(VkDevice device, const VkValidationCacheCreateInfoEXT& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif