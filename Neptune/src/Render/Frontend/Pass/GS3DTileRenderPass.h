/**
* @file GS3DTileRenderPass.h.
* @brief The GS3DTileRenderPass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Pass.h"

#include <glm/vec2.hpp>

namespace Neptune::RHI {
    
    class Pipeline;
    class DescriptorList;
    class Buffer;
    class RenderPass;
}

namespace Neptune::Render { 

    /**
    * @brief GS3DTileRenderPass Class
    */
    class GS3DTileRenderPass : public Pass
    {
    public:

        /**
        * @brief Constructor Function.
        */
        GS3DTileRenderPass() : Pass() {}
		
        /**
        * @brief Destructor Function.
        */
        ~GS3DTileRenderPass() override = default;

        /**
        * @brief Interface of Construct.
        */
        void OnConstruct() override;

        /**
        * @brief Interface of CollectRHI.
        *
        * @param[in] scene Scene.
        */
        void OnCollectRHI(Scene* scene, RHI::CmdList& cmdList) override;

        /**
        * @brief Set this Pass FrameBuffer Attachment Size.
        *
        * @param[in] rtSize FrameBuffer Attachment Size.
        */
        void SetRTSize(const glm::vec2& rtSize) { m_RTSize = rtSize; }
        
    private:
        
        // PreProcess
        InFlightResource<RHI::DescriptorList> m_PreProcessDescriptorList;    // @brief PreProcess DescriptorList
        SP<RHI::Pipeline>                     m_PreProcessPipeline;          // @brief PreProcess Pipeline

        // Setup
        InFlightResource<RHI::DescriptorList> m_SetupDescriptorList;         // @brief Setup DescriptorList
        SP<RHI::Pipeline>                     m_SetupPipeline;               // @brief Setup Pipeline

        // Histogram
        InFlightResource<RHI::DescriptorList> m_HistogramDescriptorList;     // @brief Histogram DescriptorList
        SP<RHI::Pipeline>                     m_HistogramPipeline;           // @brief Histogram Pipeline

        // Scan
        InFlightResource<RHI::DescriptorList> m_ScanDescriptorList;          // @brief Scan DescriptorList
        SP<RHI::Pipeline>                     m_ScanPipeline;                // @brief Scan Pipeline

        // Scatter
        InFlightResource<RHI::DescriptorList> m_ScatterDescriptorList;       // @brief Scatter DescriptorList
        SP<RHI::Pipeline>                     m_ScatterPipeline;             // @brief Scatter Pipeline

        // Range
        InFlightResource<RHI::DescriptorList> m_RangeDescriptorList;         // @brief Range DescriptorList
        SP<RHI::Pipeline>                     m_RangePipeline;               // @brief Range Pipeline
        
        // TileRender
        InFlightResource<RHI::DescriptorList> m_TileRenderDescriptorList;    // @brief TileRender DescriptorList
        SP<RHI::Pipeline>                     m_TileRenderPipeline;          // @brief TileRender Pipeline
        
        InFlightResource<RHI::Buffer> m_SplatBuffer;                         // @brief Splat Buffer
        InFlightResource<RHI::Buffer> m_EntryBufferA;                        // @brief Entry BufferA
        InFlightResource<RHI::Buffer> m_EntryBufferB;                        // @brief Entry BufferB
        InFlightResource<RHI::Buffer> m_HistBuffer;                          // @brief Hist Buffer
        InFlightResource<RHI::Buffer> m_InfoBuffer;                          // @brief Info Buffer
        InFlightResource<RHI::Buffer> m_RangeBuffer;                         // @brief Range Buffer
        
        glm::vec2 m_RTSize{ 100.0f, 100.0f };                            // @brief RenderTarget Size
    };
}