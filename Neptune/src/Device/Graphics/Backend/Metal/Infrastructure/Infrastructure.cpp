/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Infrastructure.h"

namespace Neptune::Metal {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
	    using enum EInfrastructure;
		
        switch (GetEInfrastructure())
        {
            default:                                 return "NonNamed";
        }
    }
}

#endif