/**
* @file AccessibleInfrastructures.cpp.
* @brief The AccessibleInfrastructures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "AccessibleInfrastructures.h"
#include "Device.h"

namespace Neptune::Metal {

	AccessibleInfrastructures::AccessibleInfrastructures(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	void AccessibleInfrastructures::Create()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Context = CreateSP<AContext>();
		
		m_Context->Registry<ADevice>(Infrastructure::GetContext().Get<IDevice>()->Handle());
	}
}

#endif