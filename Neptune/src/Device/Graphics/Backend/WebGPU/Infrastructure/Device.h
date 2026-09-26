/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Device.h"

namespace Neptune::WebGPU {

    using IDevice = IInfrastructure<class Device, EInfrastructure::Device>;

    /**
    * @brief WebGPU::Device Class.
    * This class defines the WebGPU::Device behaves.
    */
    class Device : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Device(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Device() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Device::Handle& Handle() const { return m_Device.GetHandle(); }
        
    private:

        /**
        * @brief Create Device.
        */
        void Create();
        
        /**
        * @brief Get Lost Future.
        */
        void GetLostFuture();

        /**
        * @brief Pop Error Scope from Device.
        */
        void PopErrorScope();

        /**
        * @brief Push Error Scope to Device.
        */
        void PushErrorScope();

    private:

        Unit::Device m_Device;  // @brief This Device.
    };
    
}

#endif