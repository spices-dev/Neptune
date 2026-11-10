/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Infrastructure.h"

namespace Neptune::WebGPU {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
	    using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
			case Extensions:                                          return "Extensions";
			case Instance:                                            return "Instance";
			case DebugUtilsObject:                                    return "DebugUtilsObject";
			case Adapter:                                             return "Adapter";
			case Device:                                              return "Device";
			case Surface:                                             return "Surface";
			case Queue:                                               return "Queue";
			case GraphicTimeLine:                                     return "GraphicTimeLine";
			case ComputeTimeLine:                                     return "ComputeTimeLine";
			case GraphicCommandEncoder:                               return "GraphicCommandEncoder";
			case ComputeCommandEncoder:                               return "ComputeCommandEncoder";
			case GarbageCollection:                                   return "GarbageCollection";
			case AccessibleInfrastructures:                           return "AccessibleInfrastructures";
            default:                                                  return "NonNamed";
        }
    }
}

#endif