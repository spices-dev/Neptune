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

#include <entt.hpp>

namespace Neptune::WebGPU::Unit {

	using namespace Graphic::Common;
	
	template<typename T>
	requires IsUnit<Graphic::Common::Unit<T, entt::type_hash<T>::value()>>
	using Unit = Graphic::Common::Unit<T, entt::type_hash<T>::value()>;

}

#endif