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
        NEPTUNE_PROFILE_ZONE

	    using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            case WindowContext:                      return "WindowContext";
            case DebugUtilsObject:                   return "DebugUtilsObject";
            case GraphicFence:                       return "GraphicFence";

            default:                                 return "NonNamed";
        }
    }
}

#endif