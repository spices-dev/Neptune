/**
* @file Capabilities.h.
* @brief The Capabilities Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Capability/Context.h"

namespace Neptune::OpenGL {

    using ICapabilities     = IInfrastructure<class Capabilities, EInfrastructure::Capabilities>;

    /**
    * @brief OpenGL::Capabilities Class.
    * This class defines the OpenGL::Capabilities behaves.
    */
    class Capabilities : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Capabilities(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Capabilities() override = default;

    private:

        /**
        * @brief Create Fence.
        */
        void Create();

    private:

        Capability::CContext<ECapability> m_Context;            // @brief This CContext.
        std::vector<const char*> m_Extensions;                  // @brief Extensions.
    };
	
}

#endif