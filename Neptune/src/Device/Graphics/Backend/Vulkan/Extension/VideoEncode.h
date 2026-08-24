/**
* @file VideoEncode.h.
* @brief The VideoEncode Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVideoEncode = IExtension<class VideoEncode, EExtension::VideoEncode>;
    
    class VideoEncode : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        VideoEncode();
        
        /**
        * @brief Destructor Function.
        */
        ~VideoEncode() override = default;
    };
}

#endif