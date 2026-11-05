/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Infrastructure.h"

namespace Neptune::OpenGL {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
	    using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            case WindowContext:                      return "WindowContext";
            case DebugUtilsObject:                   return "DebugUtilsObject";
            case TimeLine:                           return "TimeLine";

            default:                                 return "NonNamed";
        }
    }
}

#endif