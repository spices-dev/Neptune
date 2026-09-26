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
		
		{
			WGPUPrimitiveState                         state{};
			state.topology                           = WGPUPrimitiveTopology_TriangleList;
			state.stripIndexFormat                   = WGPUIndexFormat_Uint32;
			state.frontFace                          = WGPUFrontFace_CCW;
			state.cullMode                           = WGPUCullMode_Back;
			state.unclippedDepth                     = true;

			m_PrimitiveState                         = state;
		}

		{
			WGPUMultisampleState                       state{};
		    state.count                              = 1;
		    state.mask                               = 0;
		    state.alphaToCoverageEnabled             = false;

			m_MultisampleState                       = state;
		}
		
		{
			WGPUDepthStencilState                      state{};
			state.format                             = WGPUTextureFormat_Depth24PlusStencil8;
			state.depthWriteEnabled                  = WGPUOptionalBool_True;
			state.depthCompare                       = WGPUCompareFunction_GreaterEqual;
			state.stencilFront                       = { WGPUCompareFunction_Always, WGPUStencilOperation_Keep, WGPUStencilOperation_Keep, WGPUStencilOperation_Keep };
			state.stencilBack                        = state.stencilFront;
			state.stencilReadMask                    = 0xFFFFFFFF;
			state.stencilWriteMask                   = 0xFFFFFFFF;
			state.depthBias                          = 0;
			state.depthBiasSlopeScale                = 0.0f;
			state.depthBiasClamp                     = 0.0f;

			m_DepthStencilState                      = state;
		}
	}

	void Pipeline::SetVertexAttributeLayout()
	{

	}

	void Pipeline::SetDescriptorList(const SP<RHI::DescriptorList>& descriptorList)
	{
		NEPTUNE_PROFILE_ZONE
		
		WGPUPipelineLayoutDescriptor          desc{};
		desc.bindGroupLayoutCount           = 0;
		desc.bindGroupLayouts               = nullptr;
		desc.immediateSize                  = 0;
		
		m_PipelineLayout.CreatePipelineLayout(GetContext().Get<IDevice>()->Handle(), desc);

		DEBUGUTILS_SETOBJECTNAME(m_PipelineLayout, "PipelineLayout")
	}

	void Pipeline::SetCullMode(ECullMode mode)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_PrimitiveState.cullMode = ToWGPUCullMode(mode);
	}
	
	void Pipeline::SetTopology(ETopology topology)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_PrimitiveState.topology = ToWGPUPrimitiveTopology(topology);
	}

	void Pipeline::AddShader(ShaderStage stage, const SP<RHI::Shader>& shader)
	{
		NEPTUNE_PROFILE_ZONE

		auto p = shader->GetRHIImpl<Shader>();

		if (stage == ShaderStage::Vertex)
		{
			WGPUVertexState             state{};
			state.module              = p->Handle();
			state.entryPoint          = { "main", WGPU_STRLEN };
			state.constantCount       = 0;
			state.constants           = nullptr;
			state.bufferCount         = 0;
			state.buffers             = nullptr;

			m_VertexState = state;
		}
		else if (stage == ShaderStage::Fragment)
		{
			WGPUFragmentState           state{};
			state.module              = p->Handle();
			state.entryPoint          = { "main", WGPU_STRLEN };
			state.constantCount       = 0;
			state.constants           = nullptr;
			state.targetCount         = 0;
			state.targets             = nullptr;

			m_FragmentState = state;
		}
		else if (stage == ShaderStage::Compute)
		{
			WGPUComputeState            state{};
			state.module              = p->Handle();
			state.entryPoint          = { "main", WGPU_STRLEN };
			state.constantCount       = 0;
			state.constants           = nullptr;

			m_ComputeState = state;
		}
	}

	void Pipeline::BuildGraphicPipeline()
	{
		NEPTUNE_PROFILE_ZONE

		WGPURenderPipelineDescriptor      desc{};
		desc.layout                     = m_PipelineLayout.GetHandle();
		desc.vertex                     = m_VertexState;
		desc.primitive                  = m_PrimitiveState;
		desc.depthStencil               = &m_DepthStencilState;
		desc.multisample                = m_MultisampleState;
		desc.fragment                   = &m_FragmentState;
		
		m_Pipeline.CreateRenderPipeline(desc);
	}
	
	void Pipeline::BuildComputePipeline()
	{
		NEPTUNE_PROFILE_ZONE
		
		WGPUComputePipelineDescriptor     desc{};
		desc.layout                     = m_PipelineLayout.GetHandle();
		desc.compute                    = m_ComputeState;
		
		m_Pipeline.CreateComputePipeline(desc);
	}
	
}

#endif