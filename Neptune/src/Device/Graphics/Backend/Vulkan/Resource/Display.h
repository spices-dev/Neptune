/**
* @file Display.h.
* @brief The Display Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Surface.h"

namespace Neptune::Vulkan::Resource {

    /**
    * @brief Vulkan::Display Class.
    * This class defines the Vulkan::Display behaves.
    */
    class Display : public ContextAccessor
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit Display(Context& context) : ContextAccessor(context) {}

        /**
        * @brief Destructor Function.
        */
        ~Display() override = default;
        
        /**
        * @brief Create Display.
        */
        void CreateDisplay();
        
    private:
        
        Unit::Surface m_Surface;  // @brief Surface
    };
}

#endif