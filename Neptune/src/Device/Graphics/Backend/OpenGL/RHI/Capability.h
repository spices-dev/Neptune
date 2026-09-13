/**
* @file Capability.h.
* @brief The Capability Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/Capability.h"

namespace Neptune::OpenGL {

    /**
    * @brief OpenGL::Capability Class.
    * This class defines the OpenGL::Capability behaves.
    */
    class Capability : public ContextAccessor, public RHI::RHICapability::Impl
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit Capability(Context& context) : ContextAccessor(context) {}

        /**
        * @brief Destructor Function.
        */
        ~Capability() override = default;
        
        /**
        * @brief Is Capability Support.
        * 
        * @param[in] capability Graphic::ECapability.
        * 
        * @return Returns true if succeeded.
        */
        bool IsSupport(Graphic::ECapability capability) override;
        
        /**
        * @brief Is Pipeline Support.
        * 
        * @param[in] capability Graphic::EPipeline.
        * 
        * @return Returns true if succeeded.
        */
        bool IsSupport(Graphic::EPipeline capability) override;
		
        /**
        * @brief Is Shader Support.
        * 
        * @param[in] capability Graphic::EShader.
        * 
        * @return Returns true if succeeded.
        */
        bool IsSupport(Graphic::EShader capability) override;
		
        /**
        * @brief Is Query Support.
        * 
        * @param[in] capability Graphic::EQuery.
        * 
        * @return Returns true if succeeded.
        */
        bool IsSupport(Graphic::EQuery capability) override;
    };
}

#endif
