/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Infrastructure.h"

namespace Neptune::Vulkan {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

	    using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            case Functions:                          return "Functions";
            case Layers:                             return "Layers";
            case Extensions:                         return "Extensions";
            case Instance:                           return "Instance";
            case DebugUtilsObject:                   return "DebugUtilsObject";
            case Surface:                            return "Surface";
            case PhysicalDevice:                     return "PhysicalDevice";
            case Device:                             return "Device";
                                                                      
            case GraphicQueue:                       return "GraphicQueue";
            case PresentQueue:                       return "PresentQueue";
            case ComputeQueue:                       return "ComputeQueue";
                                                                      
            case GraphicThreadQueue:                 return "GraphicThreadQueue";
            case ComputeThreadQueue:                 return "ComputeThreadQueue";
            case TransferThreadQueue:                return "TransferThreadQueue";
            case VideoEncodeThreadQueue:             return "VideoEncodeThreadQueue";
            case VideoDecodeThreadQueue:             return "VideoDecodeThreadQueue";
            case OpticalFlowThreadQueue:             return "OpticalFlowThreadQueue";
                                                                      
            case MemoryAllocator:                    return "MemoryAllocator";
            case SwapChain:                          return "SwapChain";
                                                     
            case GraphicImageSemaphore:              return "GraphicImageSemaphore";
            case GraphicQueueSemaphore:              return "GraphicQueueSemaphore";
            case GraphicFence:                       return "GraphicFence";
                                                     
            case ComputeQueueSemaphore:              return "ComputeQueueSemaphore";
            case ComputeFence:                       return "ComputeFence";
                                                     
            case GraphicCommandPool:                 return "GraphicCommandPool";
            case GraphicCommandBuffer:               return "GraphicCommandBuffer";
                                                     
            case ComputeCommandPool:                 return "ComputeCommandPool";
            case ComputeCommandBuffer:               return "ComputeCommandBuffer";
                                                                      
            case GraphicThreadCommandPool:           return "GraphicThreadCommandPool";
            case ComputeThreadCommandPool:           return "ComputeThreadCommandPool";
            case TransferThreadCommandPool:          return "TransferThreadCommandPool";
            case VideoEncodeThreadCommandPool:       return "VideoEncodeThreadCommandPool";
            case VideoDecodeThreadCommandPool:       return "VideoDecodeThreadCommandPool";
            case OpticalFlowThreadCommandPool:       return "OpticalFlowThreadCommandPool";

            case DescriptorPool:                     return "DescriptorPool";

            default:                                 return "NonNamed";
        }
    }
}

#endif