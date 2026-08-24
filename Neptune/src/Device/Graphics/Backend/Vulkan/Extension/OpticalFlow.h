/**
* @file OpticalFlow.h.
* @brief The OpticalFlow Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IOpticalFlow = IExtension<class OpticalFlow, EExtension::OpticalFlow>;
    
    class OpticalFlow : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        OpticalFlow();
        
        /**
        * @brief Destructor Function.
        */
        ~OpticalFlow() override = default;
    };
}

#endif