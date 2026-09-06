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
        InFlightResource<RHI::DescriptorList> m_KDescriptorList;     // @brief KeyGen DescriptorList
        SP<RHI::Pipeline> m_KPipeline;                               // @brief KeyGen Pipeline
        
        // Sort
        InFlightResource<RHI::DescriptorList> m_SDescriptorList;     // @brief Sort DescriptorList
        SP<RHI::Pipeline> m_SPipeline;                               // @brief Sort Pipeline

        InFlightResource<RHI::Buffer> m_SortBuffer;                  // @brief Sort Buffer
    };
}