/**
* @file AutoreleasePool.h.
* @brief The AutoreleasePool Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Metal/Unit/AutoreleasePool.h"

namespace Neptune::Metal {

    using IFrameAutoreleasePool = IInfrastructure<class AutoreleasePool, EInfrastructure::FrameAutoreleasePool>;

    /**
    * @brief Metal::AutoreleasePool Class.
    * This class defines the Metal::AutoreleasePool behaves.
    */
    class AutoreleasePool : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        AutoreleasePool(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~AutoreleasePool() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::AutoreleasePool::Handle& Handle() const { return m_AutoreleasePool->GetHandle(); }

        /**
        * @brief Init AutoreleasePool.
        */
        void Init();
        
        /**
        * @brief Release AutoreleasePool.
        */
        void Release();
        
    private:

        UP<Unit::AutoreleasePool> m_AutoreleasePool;  // @brief this AutoreleasePool.
    };
	
}

#endif