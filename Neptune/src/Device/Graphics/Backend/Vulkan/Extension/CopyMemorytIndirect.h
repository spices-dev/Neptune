/**
* @file CopyMemorytIndirect.h.
* @brief The CopyMemorytIndirect Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ICopyMemorytIndirect = IExtension<class CopyMemorytIndirect, EExtension::CopyMemorytIndirect>;

    /**
    * @brief Used In:
    * VK_LAYER_KHRONOS_validation gpu_dump_copy_memory_indirect
    */
    class CopyMemorytIndirect : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit CopyMemorytIndirect(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~CopyMemorytIndirect() override = default;
    };
}

#endif