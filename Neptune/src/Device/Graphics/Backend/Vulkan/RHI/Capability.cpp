/**
* @file Capability.cpp.
* @brief The Capability Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Capability.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/OpticalFlow.h"
#include "Device/Graphics/Backend/Vulkan/Extension/VideoEncode.h"
#include "Device/Graphics/Backend/Vulkan/Extension/VideoDecode.h"
#include "Device/Graphics/Backend/Vulkan/Extension/MeshShader.h"
#include "Device/Graphics/Backend/Vulkan/Extension/RayTracing.h"

namespace Neptune::Vulkan {
    
    bool Capability::IsSupport(Graphic::ECapability capability)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum Graphic::ECapability;
        
        switch (capability)
        {
            case Pipeline:                        return true;
            case Shader:                          return true;
            case Query:                           return true;
            case OpticalFlow:                     return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IOpticalFlow>();
            case VideoEncode:                     return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IVideoEncode>();
            case VideoDecode:                     return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IVideoDecode>();
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
            case Mesh:                       return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IMeshShader>();
            case Compute:                    return true;
            case RayTracing:                 return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>();
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
            case Task:                        return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IMeshShader>();   
            case Mesh:                        return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IMeshShader>();   
            case Compute:                     return true;   
            case RayGeneration:               return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>();   
            case Intersection:                return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>();    
            case AnyHit:                      return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>();    
            case ClosestHit:                  return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>();    
            case Miss:                        return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>();    
            case Callable:                    return GetContext().Get<IExtensions>()->GetContext().Has<Extension::IRayTracing>(); 
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
            case ResultStatus:                    return true;
            case VideoEncodeFeedback:             return false;
            default:                              return false;
        }
    }
}

#endif