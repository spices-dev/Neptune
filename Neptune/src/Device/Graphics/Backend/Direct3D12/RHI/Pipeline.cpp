/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Pipeline.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/DescriptorList.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/Shader.h"

namespace Neptune::Direct3D12 {

	void Pipeline::SetDefault()
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void Pipeline::SetVertexAttributeLayout()
	{

	}

	void Pipeline::SetDescriptorList(const SP<RHI::DescriptorList>& descriptorList)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void Pipeline::SetCullMode(ECullMode mode)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void Pipeline::SetTopology(ETopology topology)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void Pipeline::AddShader(ShaderStage stage, const SP<RHI::Shader>& shader)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void Pipeline::BuildGraphicPipeline()
	{
		NEPTUNE_PROFILE_ZONE

	}
	
	void Pipeline::BuildComputePipeline()
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
}

#endif