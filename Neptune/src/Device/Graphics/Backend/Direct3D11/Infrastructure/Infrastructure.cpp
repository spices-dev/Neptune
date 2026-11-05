/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Infrastructure.h"

namespace Neptune::Direct3D11 {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
        : Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
	    using enum EInfrastructure;
	    
        switch (GetEInfrastructure())
        {
            case DebugUtilsObject:                   return "DebugUtilsObject";
            case DeviceContext:                      return "DeviceContext";
            case Factory:                            return "Factory";
            case Device:                             return "Device";
            case SwapChain:                          return "SwapChain";
            case GraphicFence:                       return "GraphicFence";
            case ComputeFence:                       return "ComputeFence";
            case GraphicCommandList:                 return "GraphicCommandList";
            case ComputeCommandList:                 return "ComputeCommandList";
            case GraphicThreadCommandList:           return "GraphicThreadCommandList";
            case ComputeThreadCommandList:           return "ComputeThreadCommandList";
            default:                                                  return "NonNamed";
        }
    }
}

#endif