/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Infrastructure.h"

namespace Neptune::Metal {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
	    using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
	        case FrameAutoreleasePool:               return "FrameAutoreleasePool";
	        case Device:                             return "Device";
	        case Layer:                              return "Layer";
	        case CommandQueue:                       return "CommandQueue";
	        case CommandBuffer:                      return "CommandBuffer";
	        case GraphicDispatchSemaphore:           return "GraphicDispatchSemaphore";
	        case GarbageCollection:                  return "GarbageCollection";
	        case AccessibleInfrastructures:          return "AccessibleInfrastructures";
            default:                                 return "NonNamed";
        }
    }
}

#endif