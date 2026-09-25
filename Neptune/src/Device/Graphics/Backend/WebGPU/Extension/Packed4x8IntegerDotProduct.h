/**
* @file Packed4x8IntegerDotProduct.h.
* @brief The Packed4x8IntegerDotProduct Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IPacked4x8IntegerDotProduct = IExtension<class Packed4x8IntegerDotProduct, EExtension::Packed4x8IntegerDotProduct>;
    
    class Packed4x8IntegerDotProduct : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Packed4x8IntegerDotProduct(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Packed4x8IntegerDotProduct() override = default;
    };
}

#endif