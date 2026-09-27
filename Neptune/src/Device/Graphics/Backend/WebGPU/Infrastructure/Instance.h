/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Instance.h"

namespace Neptune::WebGPU {

    using IInstance = IInfrastructure<class Instance, EInfrastructure::Instance>;

    /**
    * @brief WebGPU::Instance Class.
    * This class defines the WebGPU::Instance behaves.
    */
    class Instance : public Infrastructure
    { 
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Instance(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Instance() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Instance::Handle& Handle() const { return m_Instance.GetHandle(); }

        /**
        * @brief Process Events.
        */
        void ProcessEvents() const;
        
    private:

        /**
        * @brief Create Instance.
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

        /**
        * @brief Check WGSLFeature Requirements Satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool CheckWGSLFeatureRequirementsSatisfied();
        
    private:

        Unit::Instance                       m_Instance;    // @brief This Instance.
        std::vector<WGPUInstanceFeatureName> m_Features;    // @brief WGPUInstanceFeatureName.
        WGPUInstanceLimits                   m_Limits{};    // @brief WGPUInstanceLimits.
        
    };
    
}

#endif