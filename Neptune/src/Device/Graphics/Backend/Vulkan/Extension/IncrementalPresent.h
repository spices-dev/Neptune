/**
* @file IncrementalPresent.h.
* @brief The IncrementalPresent Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IIncrementalPresent = IExtension<class IncrementalPresent, EExtension::IncrementalPresent>;
    
    class IncrementalPresent : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit IncrementalPresent(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~IncrementalPresent() override = default;
    };
}

#endif