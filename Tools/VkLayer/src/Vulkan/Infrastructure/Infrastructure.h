/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Context.h"

#include <string>

namespace Neptune::Vulkan {
    
    /**
    * @brief Vulkan::Infrastructure Class.
    * This class defines the Vulkan::Infrastructure behaves.
    */
    class Infrastructure
    {
    public:

        /**
        * @brief Destructor Function.
        */
        virtual ~Infrastructure() = default;
    };

}