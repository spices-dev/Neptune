/**
* @file MemoryBudget.h.
* @brief The MemoryBudget Class Definitions.
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
        * 
        * @param[in] state EExtensionState.
        */
        explicit MemoryBudget(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~MemoryBudget() override = default;
    };
}

#endif