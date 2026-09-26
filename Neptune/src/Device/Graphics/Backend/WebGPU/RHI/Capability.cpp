/**
* @file Capability.cpp.
* @brief The Capability Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Capability.h"

namespace Neptune::WebGPU {
    
    bool Capability::IsSupport(Graphic::ECapability capability)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum Graphic::ECapability;
        
        switch (capability)
        {
            case Pipeline:                        return true;
            case Shader:                          return true;
            case Query:                           return false;
            case OpticalFlow:                     return false;
            case VideoEncode:                     return false;
            case VideoDecode:                     return false;
            default:                              return false;
        }
    }

    bool Capability::IsSupport(Graphic::EPipeline capability)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum Graphic::EPipeline;
        
        switch (capability)
        {
            case Rasterization:              return true;
            case Mesh:                       return false;
            case Compute:                    return true;
            case RayTracing:                 return false;
            case DataGraph:                  return false;
            case ExecutionGraph:             return false;
            default:                         return false;
        }
    }

    bool Capability::IsSupport(Graphic::EShader capability)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum Graphic::EShader;
        
        switch (capability)
        {
            case Vertex:                      return true;                 
            case TessellationControl:         return false;      
            case TessellationEvaluation:      return false;     
            case Geometry:                    return false;     
            case ClusterCulling:              return false;    
            case Fragment:                    return true;    
            case Task:                        return false;   
            case Mesh:                        return false;   
            case Compute:                     return true;   
            case RayGeneration:               return false;   
            case Intersection:                return false;    
            case AnyHit:                      return false;    
            case ClosestHit:                  return false;    
            case Miss:                        return false;    
            case Callable:                    return false; 
            default:                          return false;
        }
    }

    bool Capability::IsSupport(Graphic::EQuery capability)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum Graphic::EQuery;
        
        switch (capability)
        {
            case Occlusion:                       return false;
            case PipelineStatistics:              return false;
            case Timestamp:                       return false;
            case ElapsedTimer:                    return false;
            case Performance:                     return false;
            case TransformFeedback:               return false;
            case PrimitivesGenerated:             return false;
            case MeshShader:                      return false;
            case ResultStatus:                    return false;
            case VideoEncodeFeedback:             return false;
            default:                              return false;
        }
    }
}

#endif