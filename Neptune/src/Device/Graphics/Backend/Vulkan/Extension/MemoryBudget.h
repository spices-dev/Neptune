/**
* @file MemoryBudget.h.
* @brief The MemoryBudget Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IMemoryBudget = IExtension<class MemoryBudget, EExtension::MemoryBudget>;
    
    class MemoryBudget : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        MemoryBudget();
        
        /**
        * @brief Destructor Function.
        */
        ~MemoryBudget() override = default;
    };
}

#endif