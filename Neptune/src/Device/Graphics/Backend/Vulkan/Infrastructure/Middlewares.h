/**
* @file Middlewares.h.
* @brief The Middlewares Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/Context.h"

namespace Neptune::Vulkan {

    using IMiddlewares = IInfrastructure<class Middlewares, EInfrastructure::Middlewares>;

    /**
    * @brief Vulkan::Middlewares Class.
    * This class defines the Vulkan::Middlewares behaves.
    */
    class Middlewares : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Middlewares(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Middlewares() override = default;

        /**
        * @brief Get Middleware::MContext.
        * 
        * @return Returns EMiddleware::MContext.
        */
        const SP<Middleware::MContext<EMiddleware>>& GetContext() const { return m_Context; }
        
    private:

        /**
        * @brief Create Queue.
        */
        void Create();
        
    private:
    
        SP<Middleware::MContext<EMiddleware>> m_Context; // @brief This MContext.
        
    };

}

#endif