/**
* @file DescriptorList.cpp.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DescriptorList.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/RenderTarget.h"

namespace Neptune::Direct3D12 {

	void DescriptorList::AddShaderConstant(uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void DescriptorList::AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void DescriptorList::AddDynamicUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void DescriptorList::AddUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void DescriptorList::AddStorageTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void DescriptorList::UpdateUniformBuffer(uint32_t set, uint32_t binding, const void* data)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void DescriptorList::UpdateUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void DescriptorList::UpdateStorageTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void DescriptorList::UpdateDynamicUniformBufferOffset(uint32_t set, uint32_t offset)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void DescriptorList::CombineSharedLayout(const RHI::RHIDescriptorList::Impl* shared)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void DescriptorList::Build()
	{
		NEPTUNE_PROFILE_ZONE
		
		D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc{};
		
		m_RootSignature.CreateRootSignature(GetContext().Get<IDevice>()->Handle(), desc);
	}
}

#endif