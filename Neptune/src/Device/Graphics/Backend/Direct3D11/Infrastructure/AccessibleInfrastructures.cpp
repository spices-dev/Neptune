/**
* @file AccessibleInfrastructures.cpp.
* @brief The AccessibleInfrastructures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "AccessibleInfrastructures.h"
#include "Device.h"
#include "DeviceContext.h"

namespace Neptune::Direct3D11 {

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
		m_Context->Registry<ADeviceContext>(Infrastructure::GetContext().Get<IDeviceContext>()->Handle());
	}
}

#endif