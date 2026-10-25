/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Pipeline.h"
#include "Device/Graphics/Backend/Direct3D12/Converter.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/DescriptorList.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/Shader.h"

namespace Neptune::Direct3D12 {

	void Pipeline::SetDefault()
	{
		NEPTUNE_PROFILE_ZONE
		
		{
			CD3DX12_RASTERIZER_DESC                       rasterizer{};
			rasterizer.FillMode                         = D3D12_FILL_MODE_SOLID;
			rasterizer.CullMode                         = D3D12_CULL_MODE_BACK;
			rasterizer.FrontCounterClockwise            = TRUE;
			rasterizer.DepthBias                        = D3D12_DEFAULT_DEPTH_BIAS;
			rasterizer.DepthBiasClamp                   = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterizer.SlopeScaledDepthBias             = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterizer.DepthClipEnable                  = FALSE;
			rasterizer.MultisampleEnable                = FALSE;
			rasterizer.AntialiasedLineEnable            = FALSE;
			rasterizer.ForcedSampleCount                = 0;
			rasterizer.ConservativeRaster               = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			m_PSOStream.rasterizerState                 = rasterizer;
		}
		
		{
			CD3DX12_DEPTH_STENCIL_DESC                    depthStencil{};
			depthStencil.DepthEnable                    = TRUE;
			depthStencil.DepthWriteMask                 = D3D12_DEPTH_WRITE_MASK_ALL;
			depthStencil.DepthFunc                      = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
			depthStencil.StencilEnable                  = FALSE;
			depthStencil.StencilReadMask                = D3D12_DEFAULT_STENCIL_READ_MASK;
			depthStencil.StencilWriteMask               = D3D12_DEFAULT_STENCIL_WRITE_MASK;
			depthStencil.FrontFace.StencilFailOp        = D3D12_STENCIL_OP_KEEP;
			depthStencil.FrontFace.StencilDepthFailOp   = D3D12_STENCIL_OP_KEEP;
			depthStencil.FrontFace.StencilPassOp        = D3D12_STENCIL_OP_KEEP;
			depthStencil.FrontFace.StencilFunc          = D3D12_COMPARISON_FUNC_ALWAYS;
			depthStencil.BackFace                       = depthStencil.FrontFace;

			m_PSOStream.depthStencilState               = depthStencil;
		}
		
		{
			m_PSOStream.blendState                      = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		}
		
		{
			DXGI_SAMPLE_DESC                              sample{};
			sample.Count                                = 1;
			sample.Quality                              = 0;
			
			
			m_PSOStream.sampleDesc                      = sample;
			m_PSOStream.sampleMask                      = UINT_MAX;
		}
		
		{
			m_PSOStream.DSVFormat                       = DXGI_FORMAT_D24_UNORM_S8_UINT;
		}
		
		{
			m_PSOStream.primitiveTopologyType           = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		}
	}

	void Pipeline::SetVertexAttributeLayout()
	{
		NEPTUNE_PROFILE_ZONE
	}

	void Pipeline::SetDescriptorList(const SP<RHI::DescriptorList>& descriptorList)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_PSOStream.rootSignature = descriptorList->GetRHIImpl<DescriptorList>()->Handle();
	}

	void Pipeline::SetCullMode(ECullMode mode)
	{
		NEPTUNE_PROFILE_ZONE
		
		CD3DX12_RASTERIZER_DESC rasterizerState       = m_PSOStream.rasterizerState;
		rasterizerState.CullMode                         = ToD3D12CullMode(mode);
		
		m_PSOStream.rasterizerState                      = rasterizerState;
	}
	
	void Pipeline::SetTopology(ETopology topology)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_PSOStream.primitiveTopologyType = ToD3D12PrimitiveTopologyType(topology);
	}

	void Pipeline::AddShader(ShaderStage stage, const SP<RHI::Shader>& shader)
	{
		NEPTUNE_PROFILE_ZONE

		D3D12_SHADER_BYTECODE       code{};
		code.pShaderBytecode      = shader->GetRHIImpl<Shader>()->Handle()->GetBufferPointer();
		code.BytecodeLength       = shader->GetRHIImpl<Shader>()->Handle()->GetBufferSize();
		
		switch (stage)
		{
			case ShaderStage::Vertex:   m_PSOStream.vs = code; break;
			case ShaderStage::Fragment: m_PSOStream.ps = code; break;
			case ShaderStage::Compute:  m_PSOStream.cs = code; break;
			default: break;
		}
	}

	void Pipeline::BuildGraphicPipeline()
	{
		NEPTUNE_PROFILE_ZONE

		D3D12_PIPELINE_STATE_STREAM_DESC            desc{};
		desc.SizeInBytes                          = sizeof(m_PSOStream);
		desc.pPipelineStateSubobjectStream        = &m_PSOStream;
		
		m_Pipeline.CreatePipelineState(GetContext().Get<IDevice>()->Handle(), desc);
	}
	
	void Pipeline::BuildComputePipeline()
	{
		NEPTUNE_PROFILE_ZONE
		
		BuildGraphicPipeline();
	}
	
}

#endif