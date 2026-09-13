/**
* @file ClipControl.h.
* @brief The ClipControl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IClipControl = IExtension<class ClipControl, EExtension::ClipControl>;
    
    class ClipControl : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ClipControl(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ClipControl() override = default;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
    };
}

#endif