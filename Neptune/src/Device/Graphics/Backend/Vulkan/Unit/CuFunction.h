/**
* @file CuFunction.h.
* @brief The CuFunction Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::CuFunction Class.
    * This class defines the Vulkan::Unit::CuFunction behaves.
    */
    class CuFunction : public Unit<VkCuFunctionNVX, VkObjectType::VK_OBJECT_TYPE_CU_FUNCTION_NVX>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        CuFunction() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~CuFunction() override;

        /**
        * @brief Create CuFunction.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkCuFunctionCreateInfoNVX.
        */
        void CreateCuFunction(VkDevice device, const VkCuFunctionCreateInfoNVX& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif