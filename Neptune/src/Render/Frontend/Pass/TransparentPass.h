/**
* @file TransparentPass.h.
* @brief The TransparentPass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Pass.h"

namespace Neptune::RHI {

    class RenderPass;
    class Pipeline;
    class DescriptorList;
    class IndexBuffer;
    class Buffer;
}

namespace Neptune::Render { 

    /**
    * @brief TransparentPass Class
    */
    class TransparentPass : public Pass
    {
    public:

        /**
        * @brief Constructor Function.
        */
        TransparentPass() : Pass() {}
		
        /**
        * @brief Destructor Function.
        */
        ~TransparentPass() override = default;

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

        SP<RHI::RenderPass>                    m_RenderPass;         // @brief RenderPass
        InFlightResource<RHI::DescriptorList>  m_DescriptorList;     // @brief DescriptorList
        SP<RHI::Pipeline>                      m_Pipeline;           // @brief Pipeline
        SP<RHI::IndexBuffer>                   m_IndexBuffer;        // @brief IndexBuffer
        InFlightResource<RHI::Buffer>          m_SortBuffer;         // @brief SortBuffer
    };
}