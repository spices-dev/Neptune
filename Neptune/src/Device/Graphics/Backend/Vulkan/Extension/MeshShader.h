/**
* @file MeshShader.h.
* @brief The MeshShader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IMeshShader = IExtension<class MeshShader, EExtension::MeshShader>;
    
    class MeshShader : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit MeshShader(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~MeshShader() override = default;
    };
}

#endif