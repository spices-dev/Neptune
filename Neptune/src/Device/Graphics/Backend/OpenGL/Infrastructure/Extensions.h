/**
* @file Extensions.h.
* @brief The Extensions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Extension/Context.h"

namespace Neptune::OpenGL {

    using IExtensions     = IInfrastructure<class Extensions, EInfrastructure::Extensions>;

    /**
    * @brief OpenGL::Extensions Class.
    * This class defines the OpenGL::Extensions behaves.
    */
    class Extensions : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Extensions(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Extensions() override = default;

    private:

        /**
        * @brief Create Fence.
        */
        void Create();

    private:

        Extension::EContext<EExtension> m_Context;              // @brief This EContext.
        std::vector<const char*> m_Extensions;                  // @brief Extensions.
    };
	
}

#endif