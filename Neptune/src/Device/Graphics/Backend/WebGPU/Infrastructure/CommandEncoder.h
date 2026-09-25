/**
* @file CommandEncoder.h.
* @brief The CommandEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/CommandEncoder.h"
#include "Device/Graphics/Backend/WebGPU/Unit/CommandBuffer.h"

namespace Neptune::WebGPU {

    using IGraphicCommandEncoder = IInfrastructure<class CommandEncoder, EInfrastructure::GraphicCommandEncoder>;
    using IComputeCommandEncoder = IInfrastructure<class CommandEncoder, EInfrastructure::ComputeCommandEncoder>;

    /**
    * @brief WebGPU::CommandEncoder Class.
    * This class defines the WebGPU::CommandEncoder behaves.
    */
    class CommandEncoder : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        CommandEncoder(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~CommandEncoder() override = default;

        /**
        * @brief Get CommandEncoder.
        *
        * @return Returns CommandEncoder.
        */
        SP<Unit::CommandEncoder> IHandle() const { return m_CommandEncoder; }
        
        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::CommandEncoder::Handle& Handle() const { return m_CommandEncoder->GetHandle(); }
        
        /**
        * @brief Begin CommandEncoder.
        */
        void Begin();
		
        /**
        * @brief End CommandEncoder.
        * 
        * return Returns Unit::CommandBuffer.
        */
        UP<Unit::CommandBuffer> End();

    private:

        SP<Unit::CommandEncoder> m_CommandEncoder;  // @brief CommandEncoder.
    };

}

#endif