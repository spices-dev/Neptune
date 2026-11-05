/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
//#include "RHI/RHIHeader.h"

namespace Neptune::Direct3D11 {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::Direct3D11)
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
        m_Context->Registry<IDeviceContext>();
        m_Context->Registry<IFactory>();
        m_Context->Registry<IDevice>();
        
        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);
        m_Context->Registry<IComputeFence>(MaxFrameInFlight);
        
        m_Context->Registry<IGraphicCommandList>(MaxFrameInFlight);
        m_Context->Registry<IComputeCommandList>(MaxFrameInFlight);
        
        m_Context->Registry<IAccessibleInfrastructures>();
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

    UP<RHI::RHIImplEmpty> GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
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
            case RHI::ERHI::Decoder:          NEPTUNE_LOG_CORE(E) << "Direct3D11 do not support RHI: [ " << ToString(e) << " ].";       return nullptr;
            case RHI::ERHI::OpticalFlow:      NEPTUNE_LOG_CORE(E) << "Direct3D11 do not support RHI: [ " << ToString(e) << " ].";   return nullptr;*/
            default:                          NEPTUNE_LOG_CORE(E) << "Direct3D11 do not support RHI: [ " << ToString(e) << " ].";           return nullptr;
		}
	}

    std::any GraphicsBackend::AccessInfrastructure() const
    {
        return m_Context->Get<IAccessibleInfrastructures>()->GetContext();
    }
}

#endif