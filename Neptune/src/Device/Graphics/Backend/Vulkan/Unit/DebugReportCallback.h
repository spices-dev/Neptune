/**
* @file DebugReportCallback.h.
* @brief The DebugReportCallback Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::DebugReportCallback Class.
    * This class defines the Vulkan::Unit::DebugReportCallback behaves.
    */
    class DebugReportCallback : public Unit<VkDebugReportCallbackEXT, VkObjectType::VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DebugReportCallback() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~DebugReportCallback() override;

        /**
        * @brief Create DebugReportCallback.
        *
        * @param[in] instance VkInstance.
        * @param[in] info VkDebugReportCallbackCreateInfoEXT.
        */
        void CreateDebugReportCallback(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT& info);

    private:

        VkInstance m_Instance = VK_NULL_HANDLE;       // @brief VkInstance.
    };
}

#endif