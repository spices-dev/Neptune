/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
//#include "RHI/RHIHeader.h"

namespace Neptune::Direct3D12 {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::Direct3D12)
    {
        NEPTUNE_PROFILE_ZONE

    	HandleResultDelegate::SetHandler([&](HRESULT result) { HandleResult(result); });
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE
    	
        m_Context = CreateUP<Context>();

        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IFactory>();
        m_Context->Registry<IDevice>();

        m_Context->Registry<IGraphicQueue>();
        m_Context->Registry<IComputeQueue>();
    	
        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);
        m_Context->Registry<IComputeFence>(MaxFrameInFlight);

        m_Context->Registry<IGraphicCommandList>(MaxFrameInFlight);
        m_Context->Registry<IComputeCommandList>(MaxFrameInFlight);

        m_Context->Registry<IRTVDescriptorHeap>();
        m_Context->Registry<IDSVDescriptorHeap>();
        m_Context->Registry<ISRVDescriptorHeap>();
        m_Context->Registry<IUAVDescriptorHeap>();
    }

    void GraphicsBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context->UnRegistry();
    }

    Context& GraphicsBackend::GetContext() const
    {
        return *m_Context;
    }

    void GraphicsBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE
    }

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
            /*case RHI::ERHI::RenderPass:       return std::static_pointer_cast<RHI::RHIRenderPass::Impl>        (CreateSP<RenderPass>           (*m_Context));
			case RHI::ERHI::DescriptorList:   return std::static_pointer_cast<RHI::RHIDescriptorList::Impl>    (CreateSP<DescriptorList>       (*m_Context));
			case RHI::ERHI::Pipeline:         return std::static_pointer_cast<RHI::RHIPipeline::Impl>          (CreateSP<Pipeline>             (*m_Context));
			case RHI::ERHI::Shader:           return std::static_pointer_cast<RHI::RHIShader::Impl>            (CreateSP<Shader>               (*m_Context));
			case RHI::ERHI::RenderTarget:     return std::static_pointer_cast<RHI::RHIRenderTarget::Impl>      (CreateSP<RenderTarget>         (*m_Context));
			case RHI::ERHI::VertexBuffer:     return std::static_pointer_cast<RHI::RHIVertexBuffer::Impl>      (CreateSP<VertexBuffer>         (*m_Context));
			case RHI::ERHI::IndexBuffer:      return std::static_pointer_cast<RHI::RHIIndexBuffer::Impl>       (CreateSP<IndexBuffer>          (*m_Context));
            case RHI::ERHI::CmdList:          return std::static_pointer_cast<RHI::RHICmdList::Impl>           (CreateSP<CmdList>              (*m_Context));
			case RHI::ERHI::CmdList2:         return std::static_pointer_cast<RHI::RHICmdList2::Impl>          (CreateSP<CmdList2>             (*m_Context));
            case RHI::ERHI::Decoder:          NEPTUNE_LOG_CORE(E) << "Direct3D12 do not support Decoder RHI.";       return nullptr;
            case RHI::ERHI::OpticalFlow:      NEPTUNE_LOG_CORE(E) << "Direct3D12 do not support OpticalFlow RHI.";   return nullptr;*/
            default:                          NEPTUNE_LOG_CORE(E) << "Direct3D12 do not support this RHI.";          return nullptr;
		}
	}

    AInfrastructures GraphicsBackend::AccessInfrastructure() const
    {
        NEPTUNE_PROFILE_ZONE

    	AContext context;

        context.Registry<ADevice>(m_Context->Get<IDevice>()->Handle());
		context.Registry<ACommandQueue>(m_Context->Get<IGraphicQueue>()->Handle());
		context.Registry<ARTVFormat>(DXGI_FORMAT_B8G8R8A8_UNORM);
		context.Registry<ADSVFormat>(DXGI_FORMAT_B8G8R8A8_UNORM);
		context.Registry<ASRVDescriptorHeap>(m_Context->Get<ISRVDescriptorHeap>()->Handle());
        context.Registry<ASRVCPUHandle>(m_Context->Get<ISRVDescriptorHeap>()->GetCPUDescriptorHandleForHeapStart());
        context.Registry<ASRVGPUHandle>(m_Context->Get<ISRVDescriptorHeap>()->GetGPUDescriptorHandleForHeapStart());

        return context.GetInfrastructures();
    }
}

#endif