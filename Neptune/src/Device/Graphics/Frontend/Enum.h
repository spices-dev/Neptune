/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Graphic {

    /**
    * @brief Enum of Graphics Backend.
    */
    enum class EBackend : uint8_t
    {
        WebGL = 0,            // @brief Web
        WebGPU,               // @brief Web
        OpenGL,               // @brief Any
        OpenGLES,             // @brief Mobile
        OpenGLSC,             // @brief Safety Critical
        Direct2D,             // @brief Windows 2D
        Direct3D9,            // @brief Windows
        Direct3D10,           // @brief Windows Vista/7
        Direct3D11,           // @brief Windows
        Direct3D12,           // @brief Windows
        Vulkan,               // @brief Any
        VulkanSC,             // @brief Safety Critical
        Metal,                // @brief Ios Macos Ipados
        GNM,                  // @brief PlayStation
        GNMX,                 // @brief PlayStation
        GDK,                  // @brief Xbox
        GDKX,                 // @brief Xbox
        NVN,                  // @brief Nintendo Switch

        Count
    };
    
    /**
    * @brief Enum of HDRSurface.
    */
    enum class EHDRSurface : uint8_t
    {
        PQ = 0,                         // @brief PQ
        HLG,                            // @brief HLG
        P3,                             // @brief P3
        ExSRGB,                         // @brief ExSRGB
    };
    
    /**
    * @brief Enum of Pipeline.
    */
    enum class EPipeline : uint8_t
    {
        Rasterization,                // @brief Rasterization.
        Mesh,                         // @brief Mesh.
        Compute,                      // @brief Compute.
        RayTracing,                   // @brief RayTracing.
        DataGraph,                    // @brief DataGraph.
        ExecutionGraph,               // @brief ExecutionGraph.
        
        Count,
    };
    
    /**
    * @brief Enum of Shader.
    */
    enum class EShader : uint8_t
    {
        Vertex,                           // @brief Vertex.
        TessellationControl,              // @brief TessellationControl.
        TessellationEvaluation,           // @brief TessellationEvaluation.
        Geometry,                         // @brief Geometry.
        ClusterCulling,                   // @brief ClusterCulling.
        Fragment,                         // @brief Fragment.
        Task,                             // @brief Task.
        Mesh,                             // @brief Mesh.
        Compute,                          // @brief Compute.
        RayGeneration,                    // @brief RayGeneration.
        Intersection,                     // @brief Intersection.
        AnyHit,                           // @brief AnyHit.
        ClosestHit,                       // @brief ClosestHit.
        Miss,                             // @brief Miss.
        Callable,                         // @brief Callable.
        
        Count,
    };
    
    /**
    * @brief Enum of Query.
    */
    enum class EQuery : uint8_t
    {
        Occlusion,                       // @brief Occlusion.
        PipelineStatistics,              // @brief PipelineStatistics.
        Timestamp,                       // @brief Timestamp.
        ElapsedTimer,                    // @brief ElapsedTimer.
        Performance,                     // @brief Performance.
        TransformFeedback,               // @brief TransformFeedback.
        PrimitivesGenerated,             // @brief PrimitivesGenerated.
        MeshShader,                      // @brief MeshShader.
        ResultStatus,                    // @brief ResultStatus.
        VideoEncodeFeedback,             // @brief VideoEncodeFeedback.
        
        Count,
    };
    
    /**
    * @brief Enum of Capability.
    */
    enum class ECapability  : uint8_t
    {
        Pipeline,                        // @brief Pipeline.
        Shader,                          // @brief Shader.
        Query,                           // @brief Query.
        OpticalFlow,                     // @brief OpticalFlow.
        VideoEncode,                     // @brief VideoEncode.
        VideoDecode,                     // @brief VideoDecode.
        
        Count
    };
    
    /**
    * @brief Enum of Pipeline Access.
    */
    enum class EPipelineAccess : uint8_t
    {
        None = 0,                         // @brief ShaderRead.
        ShaderRead,                       // @brief ShaderRead.
        ShaderWrite,                      // @brief ShaderWrite.
        TransferRead,                     // @brief TransferRead.
        TransferWrite,                    // @brief TransferWrite.
        IndirectCommandRead,              // @brief IndirectCommandRead.
        
        Count
    };
    
    /**
    * @brief Enum of Pipeline Stage.
    */
    enum class EPipelineStage : uint8_t
    {
        VertexShader = 0,                  // @brief VertexShader.
        FragmentShader,                    // @brief FragmentShader.
        ComputeShader,                     // @brief ComputeShader.
        TopPipeline,                       // @brief TopPipeline.
        Transfer,                          // @brief Transfer.
        DrawIndirect,                      // @brief DrawIndirect.
        Graphic,                           // @brief Graphic.
        
        Count
    };
    
    /**
    * @brief Enum of Buffer Usage.
    */
    enum class EBufferUsage : uint8_t
    {
        None = 0,                    // @brief None Usage.
        Vertex,                      // @brief VertexBuffer.
        Index,                       // @brief IndexBuffer.
        Indirect,                    // @brief IndirectBuffer.
        TransferSrc,                 // @brief TransferSrc.
        TransferDst,                 // @brief TransferDst.
        
        Count
    };
    
    /**
    * @brief Enum of Image Usage.
    */
    enum class EImageUsage : uint8_t
    {
        ColorAttachment = 0,         // @brief ColorAttachment.
        Sampler,                     // @brief Sampler.
        Storage,                     // @brief Storage.
        TransferSrc,                 // @brief TransferSrc.
        TransferDst,                 // @brief TransferDst.
        
        Count
    };
    
    /**
    * @brief Enum of Image Layout.
    */
    enum class EImageLayout : uint8_t
    {
        Undefined = 0,               // @brief None Usage.
        General,                     // @brief VertexBuffer.
        Attachment,                  // @brief Attachment.
        ShaderRead,                  // @brief ShaderRead.
        TransferSrc,                 // @brief TransferSrc.
        TransferDst,                 // @brief TransferDst.
        
        Count
    };

    /**
    * @brief Enum of Image Aspect.
    */
    enum class EImageAspect : uint8_t
    {
        Color = 0,               // @brief Color.
        Depth,                   // @brief Depth.
        Stencil,                 // @brief Stencil.
        Plane0,                  // @brief Plane0.
        Plane1,                  // @brief Plane1.
        Plane2,                  // @brief Plane2.
        
        Count
    };

}