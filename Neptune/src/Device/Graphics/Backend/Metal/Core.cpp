/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include "Core.h"

namespace Neptune::Metal {

	namespace {
	
        HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}
	
	void HandleResult()
	{
        NEPTUNE_PROFILE_ZONE
	}
}

#endif