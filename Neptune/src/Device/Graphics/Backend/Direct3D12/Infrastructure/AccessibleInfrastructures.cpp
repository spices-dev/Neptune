/**
* @file AccessibleInfrastructures.cpp.
* @brief The AccessibleInfrastructures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "AccessibleInfrastructures.h"
#include "Extensions.h"
#include "Device.h"
#include "Queue.h"
#include "DescriptorHeap.h"

namespace Neptune::Direct3D12 {

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
		m_Context->Registry<ACommandQueue>(Infrastructure::GetContext().Get<IGraphicQueue>()->Handle());
		m_Context->Registry<ARTVFormat>(DXGI_FORMAT_B8G8R8A8_UNORM);
		m_Context->Registry<ADSVFormat>(DXGI_FORMAT_B8G8R8A8_UNORM);
		m_Context->Registry<ASRVDescriptorHeap>(Infrastructure::GetContext().Get<ISRVDescriptorHeap>()->Handle());
		m_Context->Registry<ASRVCPUHandle>(Infrastructure::GetContext().Get<ISRVDescriptorHeap>()->GetCPUDescriptorHandleForHeapStart());
		m_Context->Registry<ASRVGPUHandle>(Infrastructure::GetContext().Get<ISRVDescriptorHeap>()->GetGPUDescriptorHandleForHeapStart());
	}
}

#endif