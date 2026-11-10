/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

namespace Neptune::WebGPU {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Extensions = 0,                      // @brief Extensions.
        Instance,                            // @brief Instance.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Adapter,                             // @brief Adapter.
        Device,                              // @brief LogicalDevice.
        Surface,                             // @brief Surface.

        Queue,                               // @brief Queue.
        
        GraphicTimeLine,                     // @brief GraphicTimeLine.
        ComputeTimeLine,                     // @brief ComputeTimeLine.

        GraphicCommandEncoder,               // @brief GraphicCommandEncoder.
        ComputeCommandEncoder,               // @brief ComputeCommandEncoder.
        
        GarbageCollection,                   // @brief GarbageCollection.
        AccessibleInfrastructures,           // @brief AccessibleInfrastructures.
        
        Count
    };

}

#endif