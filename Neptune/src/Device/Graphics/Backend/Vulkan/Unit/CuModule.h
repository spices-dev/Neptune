/**
* @file CuModule.h.
* @brief The CuModule Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::CuModule Class.
    * This class defines the Vulkan::Unit::CuModule behaves.
    */
    class CuModule : public Unit<VkCuModuleNVX, VkObjectType::VK_OBJECT_TYPE_CU_MODULE_NVX>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        CuModule() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~CuModule() override;

        /**
        * @brief Create CuModule.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkCuModuleCreateInfoNVX.
        */
        void CreateCuModule(VkDevice device, const VkCuModuleCreateInfoNVX& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif