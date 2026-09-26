/**
* @file Adapter.h.
* @brief The Adapter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Adapter.h"

namespace Neptune::WebGPU {

    using IAdapter = IInfrastructure<class Adapter, EInfrastructure::Adapter>;

    /**
    * @brief WebGPU::Adapter Class.
    * This class defines the WebGPU::Adapter behaves.
    */
    class Adapter : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Adapter(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Adapter() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Adapter::Handle& Handle() const { return m_Adapter.GetHandle(); }

        /**
        * @brief Get WGPUFeatureName.
        *
        * @return Returns WGPUFeatureName.
        */
        const std::vector<WGPUFeatureName>& GetFeatures() const { return m_Features; }
        
        /**
        * @brief Get WGPULimits.
        *
        * @return Returns WGPULimits.
        */
        const WGPULimits& GetLimits() const { return m_Limits; }
        
    private:

        /**
        * @brief Create Adapter.
        */
        void Create();

        /**
        * @brief Check Feature Requirements Satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool CheckFeatureRequirementsSatisfied();

        /**
        * @brief Check Limit Requirements Satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool CheckLimitRequirementsSatisfied();

    private:

        Unit::Adapter                m_Adapter;     // @brief This Adapter.
        std::vector<WGPUFeatureName> m_Features;    // @brief WGPUInstanceFeatureName.
        WGPULimits                   m_Limits;      // @brief WGPULimits.
    };
    
}

#endif