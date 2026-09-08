/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Common/Unit/Unit.h"

namespace Neptune::Vulkan::Unit {

	using namespace Graphic::Common;
	
	template<typename T, auto E>
	requires IsUnit<Graphic::Common::Unit<T, E>>
	using Unit = Graphic::Common::Unit<T, E>;
}

#endif