/**
* @file TimeLine.h.
* @brief The TimeLine Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Future.h"

namespace Neptune::WebGPU {

    using IGraphicTimeLine = IInfrastructure<class TimeLine, EInfrastructure::GraphicTimeLine>;
    using IComputeTimeLine = IInfrastructure<class TimeLine, EInfrastructure::ComputeTimeLine>;

    /**
    * @brief WebGPU::TimeLine Class.
    * This class defines the WebGPU::TimeLine behaves.
    */
    class TimeLine : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] count CommandBuffer Counts.
        */
        TimeLine(Context& context, EInfrastructure e, uint32_t count = 1);

        /**
        * @brief Destructor Function.
        */
        ~TimeLine() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @param[in] index Handle index.
        * 
        * @return Returns Unit Handle.
        */
        const Unit::Future::Handle& Handle(uint32_t index = 0) const { return m_Futures[index]->GetHandle(); }

        /**
        * @brief Set Unit Handle.
        *
        * @param[in] frameId FrameId.
        * @param[in] handle WGPUFuture.
        */
        void SetHandle(uint32_t frameId, WGPUFuture handle);
        
        /**
        * @brief Wait Future idle.
        *
        * @param[in] frameId FrameId.
        */
        void Wait(uint32_t frameId = 0) const;
        
    private:

        /**
        * @brief Create Future.
        * 
        * @param[in] count Future Counts.
        */
        void Create(uint32_t count);

    private:

        std::vector<UP<Unit::Future>> m_Futures;  // @brief Container of Futures.
    };
    
}

#endif