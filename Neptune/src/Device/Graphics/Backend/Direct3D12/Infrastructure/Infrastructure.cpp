/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Infrastructure.h"

namespace Neptune::Direct3D12 {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
        : Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
	    using enum EInfrastructure;
	    
        switch (GetEInfrastructure())
        {
            case Extensions:                         return "Extensions";
            case DebugUtilsObject:                   return "DebugUtilsObject";
            case Factory:                            return "Factory";
            case Device:                             return "Device";
            case GraphicQueue:                       return "GraphicQueue";
            case ComputeQueue:                       return "ComputeQueue";
            case SwapChain:                          return "SwapChain";
            case GraphicTimeLine:                    return "GraphicTimeLine";
            case ComputeTimeLine:                    return "ComputeTimeLine";
            case GraphicCommandList:                 return "GraphicCommandList";
            case ComputeCommandList:                 return "ComputeCommandList";
            case RTVDescriptorHeap:                  return "RTVDescriptorHeap";
            case DSVDescriptorHeap:                  return "DSVDescriptorHeap";
            case SRVDescriptorHeap:                  return "SRVDescriptorHeap";
            case UAVDescriptorHeap:                  return "UAVDescriptorHeap";
            case GarbageCollection:                  return "GarbageCollection";
            case AccessibleInfrastructures:          return "AccessibleInfrastructures";

            default:                                 return "NonNamed";
        }
    }
}

#endif