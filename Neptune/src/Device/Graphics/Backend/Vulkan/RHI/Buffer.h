/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Buffer.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"

namespace Neptune::Vulkan {

    /**
    * @brief Vulkan::Buffer Class.
    * This class defines the Vulkan::Buffer behaves.
    */
    class Buffer : public ContextAccessor, public RHI::RHIBuffer::Impl
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit Buffer(Context& context) : ContextAccessor(context) {}

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override = default;

    private:

        Unit::Buffer m_Buffer;            // @brief This Buffer.
    };
}

#endif
