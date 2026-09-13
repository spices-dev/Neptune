/**
* @file TextureFilterAnisotropic.h.
* @brief The TextureFilterAnisotropic Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ITextureFilterAnisotropic = IExtension<class TextureFilterAnisotropic, EExtension::TextureFilterAnisotropic>;
    
    class TextureFilterAnisotropic : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit TextureFilterAnisotropic(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureFilterAnisotropic() override = default;
        
        /**
        * @brief Query Extension Properties.
        */
        void QueryProperties() override;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
    private:
        
        GLfloat m_MaxAnisotropy;
    };
}

#endif