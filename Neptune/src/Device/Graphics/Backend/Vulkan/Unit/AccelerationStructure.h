/**
* @file AccelerationStructure.h.
* @brief The AccelerationStructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::AccelerationStructure Class.
    * This class defines the Vulkan::Unit::AccelerationStructure behaves.
    */
    class AccelerationStructure : public Unit<VkAccelerationStructureKHR, VkObjectType::VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        AccelerationStructure() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~AccelerationStructure() override;

        /**
        * @brief Create AccelerationStructure.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkAccelerationStructureCreateInfoKHR.
        */
        void CreateAccelerationStructure(VkDevice device, const VkAccelerationStructureCreateInfoKHR& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif