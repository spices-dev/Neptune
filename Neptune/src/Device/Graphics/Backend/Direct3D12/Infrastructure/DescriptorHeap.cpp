/**
* @file DescriptorHeap.cpp.
* @brief The DescriptorHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DescriptorHeap.h"
#include "DebugUtilsObject.h"
#include "Device.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Fence.h"

namespace Neptune::Direct3D12 {

    DescriptorHeap::DescriptorHeap(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void DescriptorHeap::Create()
    {
        NEPTUNE_PROFILE_ZONE

        D3D12_DESCRIPTOR_HEAP_DESC        desc{};
		desc.Flags                      = GetEInfrastructure() == EInfrastructure::SRVDescriptorHeap ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NumDescriptors             = 4096;
		desc.Type                       = GetDescriptorHeapType();
		desc.NodeMask                   = 0;

        m_DescriptorHeap.CreateDescriptorHeap(GetContext().Get<IDevice>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(m_DescriptorHeap, ToString())
    }

	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUDescriptorHandleForHeapStart() const
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	return m_DescriptorHeap.GetCPUDescriptorHandleForHeapStart();
    }
	
	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGPUDescriptorHandleForHeapStart() const
    {
    	NEPTUNE_PROFILE_ZONE
    	
		return m_DescriptorHeap.GetGPUDescriptorHandleForHeapStart();
    }
	
    D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeap::GetDescriptorHeapType() const
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	using enum EInfrastructure;
    	
        switch (GetEInfrastructure())
		{
			case RTVDescriptorHeap:		   return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			case DSVDescriptorHeap:        return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			case SRVDescriptorHeap:        return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			case UAVDescriptorHeap:        return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			default: return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		}
    }

}

#endif