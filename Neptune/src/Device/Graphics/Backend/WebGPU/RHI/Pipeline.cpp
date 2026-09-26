/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Pipeline.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/RHI/RenderPass.h"
#include "Device/Graphics/Backend/WebGPU/RHI/DescriptorList.h"
#include "Device/Graphics/Backend/WebGPU/RHI/Shader.h"
#include "Device/Graphics/Backend/WebGPU/Converter.h"

namespace Neptune::WebGPU {

	void Pipeline::SetDefault()
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void Pipeline::SetRenderPass(const SP<RHI::RenderPass>& renderPass)
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