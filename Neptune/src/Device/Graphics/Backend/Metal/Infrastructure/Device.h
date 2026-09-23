/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Metal/Unit/Device.h"

namespace Neptune::Metal {

    using IDevice = IInfrastructure<class Device, EInfrastructure::Device>;

    /**
    * @brief Metal::Device Class.
    * This class defines the Metal::Device behaves.
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
        
    private:

        Unit::Device m_Device;  // @brief this Device.
    };
	
}

#endif