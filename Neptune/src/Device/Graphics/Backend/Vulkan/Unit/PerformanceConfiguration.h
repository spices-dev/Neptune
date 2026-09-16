/**
* @file PerformanceConfiguration.h.
* @brief The PerformanceConfiguration Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::PerformanceConfiguration Class.
    * This class defines the Vulkan::Unit::PerformanceConfiguration behaves.
    */
    class PerformanceConfiguration : public Unit<VkPerformanceConfigurationINTEL, VkObjectType::VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        PerformanceConfiguration() = default;

        /**
        * @brief Destructor Function.
        */
        ~PerformanceConfiguration() override;

        /**
        * @brief Create PerformanceConfiguration.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkPerformanceConfigurationAcquireInfoINTEL.
        */
        void CreatePerformanceConfiguration(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif