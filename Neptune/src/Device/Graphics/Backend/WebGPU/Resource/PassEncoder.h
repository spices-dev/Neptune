/**
* @file PassEncoder.h.
* @brief The PassEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/RenderPassEncoder.h"
#include "Device/Graphics/Backend/WebGPU/Unit/ComputePassEncoder.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"

#include <variant>

namespace Neptune::WebGPU {
    
    class Pipeline;
    class DescriptorList;
}

namespace Neptune::WebGPU::Resource {

    /**
    * @brief WebGPU::PassEncoder Class.
    * This class defines the WebGPU::PassEncoder behaves.
    */
    class PassEncoder : public ContextAccessor
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit PassEncoder(Context& context) : ContextAccessor(context) {}

        /**
        * @brief Destructor Function.
        */
        ~PassEncoder() override = default;
		
        /**
        * @brief Get PassEncoder Unit Handle.
        *
        * @tparam T PassEncoder Unit
        * 
        * @return Returns PassEncoder Unit Handle.
        */
        template<IsUnitHandle T>
        void SetHandle(const T& t);
        
        /**
        * @brief Get PassEncoder Unit Handle.
        *
        * @tparam T PassEncoder Unit
        * 
        * @return Returns PassEncoder Unit Handle.
        */
        template<IsUnit T>
        T::Handle Handle() const { return std::get<UP<T>>(m_PassEncoder)->GetHandle(); }
		
        /**
        * @brief Get PassEncoder Unit.
        *
        * @tparam T PassEncoder Unit
        * 
        * @return Returns PassEncoder Unit.
        */
        template<IsUnit T>
        const UP<T>& IHandle() const { return std::get<UP<T>>(m_PassEncoder); }
        
        /**
        * @brief End Pass.
        */
        void EndPass() const;
        
        /**
        * @brief Bind Pipeline.
        *
        * @param[in] pipeline Pipeline.
        */
        void BindPipeline(const Pipeline* pipeline) const;
        
        /**
        * @brief Bind BindGroup.
        *
        * @param[in] descriptorList DescriptorList.
        */
        void BindBindGroup(const DescriptorList* descriptorList) const;
        
    private:

        std::variant<UP<Unit::RenderPassEncoder>, UP<Unit::ComputePassEncoder>> m_PassEncoder;                    // @brief PassEncoder.
        bool                                                                    m_RenderBindPoint = true;         // @brief RenderBindPoint.
    };

    template <>
    inline void PassEncoder::SetHandle<Unit::RenderPassEncoder::Handle>(const Unit::RenderPassEncoder::Handle& t)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto p = CreateUP<Unit::RenderPassEncoder>();
        
        p->SetHandle(t);
        
        DEBUGUTILS_SETOBJECTNAME(*p, "RenderPassEncoder")
        
        m_PassEncoder = std::move(p);
        
        m_RenderBindPoint = true;
    }
    
    template <>
    inline void PassEncoder::SetHandle<Unit::ComputePassEncoder::Handle>(const Unit::ComputePassEncoder::Handle& t)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto p = CreateUP<Unit::ComputePassEncoder>();
        
        p->SetHandle(t);
        
        DEBUGUTILS_SETOBJECTNAME(*p, "ComputePassEncoder")
        
        m_PassEncoder = std::move(p);
        
        m_RenderBindPoint = false;
    }
}

#endif