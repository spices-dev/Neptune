/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGLES

#include "Infrastructure.h"

namespace Neptune::OpenGLES {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (GetEInfrastructure())
        {
            default:                                                  return "NonNamed";
        }
    }
}

#endif