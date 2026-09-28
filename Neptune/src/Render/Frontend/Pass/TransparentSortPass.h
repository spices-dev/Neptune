/**
* @file TransparentSortPass.h.
* @brief The TransparentSortPass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Pass.h"

namespace Neptune::RHI {
    
    class Pipeline;
    class DescriptorList;
    class Buffer;
}

namespace Neptune::Render { 

    /**
    * @brief TransparentSortPass Class
    */
    class TransparentSortPass : public Pass
    {
    public:

        /**
        * @brief Constructor Function.
        */
        TransparentSortPass() : Pass() {}
		
        /**
        * @brief Destructor Function.
        */
        ~TransparentSortPass() override = default;

        /**
        * @brief Interface of Construct.
        */
        void OnConstruct() override;

        /**
        * @brief Interface of CollectRHI.
        *
        * @param[in] scene Scene.
        */
        void OnCollectRHI(Scene* scene) override;

    private:
        
        // KeyGen
        InFlightResource<RHI::DescriptorList> m_KGenDescriptorList;          // @brief KeyGen DescriptorList
        SP<RHI::Pipeline> m_KGenPipeline;                                    // @brief KeyGen Pipeline

        // Histogram
        InFlightResource<RHI::DescriptorList> m_HistogramDescriptorList;     // @brief Histogram DescriptorList
        SP<RHI::Pipeline> m_HistogramPipeline;                               // @brief Histogram Pipeline

        // Scan
        InFlightResource<RHI::DescriptorList> m_ScanDescriptorList;          // @brief Scan DescriptorList
        SP<RHI::Pipeline> m_ScanPipeline;                                    // @brief Scan Pipeline

        // Scan
        InFlightResource<RHI::DescriptorList> m_ScatterDescriptorList;       // @brief Scatter DescriptorList
        SP<RHI::Pipeline> m_ScatterPipeline;                                 // @brief Scatter Pipeline

        InFlightResource<RHI::Buffer> m_SortBufferA;                         // @brief Sort BufferA
        InFlightResource<RHI::Buffer> m_SortBufferB;                         // @brief Sort BufferB
        InFlightResource<RHI::Buffer> m_HistBuffer;                          // @brief Hist Buffer
        
        InFlightResource<RHI::Buffer> m_IndirectBuffer;                      // @brief Indirect Buffer
    };
}