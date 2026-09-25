/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"
#include "Device/Graphics/Backend/Common/Unit/Unit.h"

namespace Neptune::WebGPU::Unit {

	namespace detail {
	
		constexpr uint32_t ignore = 0;
	}
	
	using namespace Graphic::Common;
	
	template<typename T>
	requires IsUnit<Graphic::Common::Unit<T, detail::ignore>>
	using Unit = Graphic::Common::Unit<T, detail::ignore>;

}

#endif