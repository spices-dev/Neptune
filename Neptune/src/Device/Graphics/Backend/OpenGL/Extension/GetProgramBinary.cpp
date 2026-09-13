/**
* @file GetProgramBinary.cpp.
* @brief The GetProgramBinary Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "GetProgramBinary.h"

namespace Neptune::OpenGL::Extension {

    GetProgramBinary::GetProgramBinary(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_ARB_get_program_binary");
        
        GLint count = 0;
        
        glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &count);
        
        if (count <= 0) return;
        
        m_Formats.resize(count);
        
        glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, m_Formats.data());
    }

}

#endif