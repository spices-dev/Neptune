/**
* @file FragmentDepth.h.
* @brief The FragmentDepth Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IFragmentDepth = IExtension<class FragmentDepth, EExtension::FragmentDepth>;
    
    class FragmentDepth : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit FragmentDepth(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~FragmentDepth() override = default;
    };
}

#endif