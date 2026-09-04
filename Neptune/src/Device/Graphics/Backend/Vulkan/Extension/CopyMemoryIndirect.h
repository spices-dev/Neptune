/**
* @file CopyMemoryIndirect.h.
* @brief The CopyMemoryIndirect Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ICopyMemoryIndirect = IExtension<class CopyMemoryIndirect, EExtension::CopyMemoryIndirect>;

    /**
    * @brief Used In:
    * VK_LAYER_KHRONOS_validation gpu_dump_copy_memory_indirect
    */
    class CopyMemoryIndirect : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit CopyMemoryIndirect(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~CopyMemoryIndirect() override = default;
    };
}

#endif