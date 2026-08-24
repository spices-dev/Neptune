/**
* @file VideoDecode.h.
* @brief The VideoDecode Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVideoDecode = IExtension<class VideoDecode, EExtension::VideoDecode>;
    
    class VideoDecode : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        VideoDecode();
        
        /**
        * @brief Destructor Function.
        */
        ~VideoDecode() override = default;
    };
}

#endif