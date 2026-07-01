/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Core.h"
#include "Device/Graphics/Backend/Common/Unit/Unit.h"

namespace Neptune::Direct3D12::Unit {

	namespace detail {
	
		constexpr uint32_t ignore = 0;
	}

	using namespace Render::Common;

	template<typename T>
	requires IsUnit<Render::Common::Unit<T, detail::ignore>>
	using Unit = Render::Common::Unit<T, detail::ignore>;
}

#endif