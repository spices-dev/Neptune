/**
* @file DescriptorHeap.h.
* @brief The DescriptorHeap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Resource {

    /**
    * @brief Vulkan::DescriptorHeap Class.
    * This class defines the Vulkan::DescriptorHeap behaves.
    */
    class DescriptorHeap : public ContextAccessor
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit DescriptorHeap(Context& context) : ContextAccessor(context) {}

        /**
        * @brief Destructor Function.
        */
        ~DescriptorHeap() override = default;
    };
}

#endif