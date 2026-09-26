/**
* @file DescriptorList.cpp.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "DescriptorList.h"
#include "Device/Graphics/Backend/WebGPU/RHI/RenderTarget.h"
#include "Device/Graphics/Frontend/RHI/RenderTarget.h"

namespace Neptune::WebGPU {

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

	void DescriptorList::UpdateUniformBuffer(uint32_t set, uint32_t binding, const void* data)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void DescriptorList::UpdateUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
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

		auto p = dynamic_cast<const DescriptorList*>(shared);
		
	}

	void DescriptorList::Build()
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	
}

#endif