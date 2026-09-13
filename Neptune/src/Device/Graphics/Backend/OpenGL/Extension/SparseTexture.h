/**
* @file SparseTexture.h.
* @brief The SparseTexture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ISparseTexture = IExtension<class SparseTexture, EExtension::SparseTexture>;
    
    class SparseTexture : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit SparseTexture(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~SparseTexture() override = default;
        
    private:
        
        GLint m_MaxSize;
        GLint m_Max3DSize;
        GLint m_MaxArrayLayers;
    };
}

#endif