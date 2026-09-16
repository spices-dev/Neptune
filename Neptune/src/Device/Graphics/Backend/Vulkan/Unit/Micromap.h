/**
* @file Micromap.h.
* @brief The Micromap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Micromap Class.
    * This class defines the Vulkan::Unit::Micromap behaves.
    */
    class Micromap : public Unit<VkMicromapEXT, VkObjectType::VK_OBJECT_TYPE_MICROMAP_EXT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Micromap() = default;

        /**
        * @brief Destructor Function.
        */
        ~Micromap() override;

        /**
        * @brief Create Micromap.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkMicromapCreateInfoEXT.
        */
        void CreateMicromap(VkDevice device, const VkMicromapCreateInfoEXT& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif