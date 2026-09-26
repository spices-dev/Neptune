/**
* @file TimestampQuery.h.
* @brief The TimestampQuery Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITimestampQuery = IExtension<class TimestampQuery, EExtension::TimestampQuery>;
    
    class TimestampQuery : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TimestampQuery(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TimestampQuery() override = default;
    };
}

#endif