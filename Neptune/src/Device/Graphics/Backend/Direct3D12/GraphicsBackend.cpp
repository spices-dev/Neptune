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
#include "RHI/RHIHeader.h"

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

        m_Context->Registry<IExtensions>();
        
#ifdef NEPTUNE_DEBUG
        
        m_Context->Registry<IDebugUtilsObject>();
        
#endif
        
        m_Context->Registry<IFactory>();
        m_Context->Registry<IDevice>();

        m_Context->Registry<IGraphicQueue>();
        m_Context->Registry<IComputeQueue>();
    	
        m_Context->Registry<IGraphicTimeLine>(MaxFrameInFlight);
        m_Context->Registry<IComputeTimeLine>(MaxFrameInFlight);

        m_Context->Registry<IGraphicCommandList>(MaxFrameInFlight);
        m_Context->Registry<IComputeCommandList>(MaxFrameInFlight);

        m_Context->Registry<IRTVDescriptorHeap>();
        m_Context->Registry<IDSVDescriptorHeap>();
        m_Context->Registry<ISRVDescriptorHeap>();
        m_Context->Registry<IUAVDescriptorHeap>();
        
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
            case RHI::ERHI::Capability:       return CreateUP<Capability>           (*m_Context);
            case RHI::ERHI::RenderPass:       return CreateUP<RenderPass>           (*m_Context);
            case RHI::ERHI::DescriptorList:   return CreateUP<DescriptorList>       (*m_Context);
            case RHI::ERHI::Pipeline:         return CreateUP<Pipeline>             (*m_Context);
            case RHI::ERHI::Shader:           return CreateUP<Shader>               (*m_Context);
            case RHI::ERHI::RenderTarget:     return CreateUP<RenderTarget>         (*m_Context);
            case RHI::ERHI::Buffer:           return CreateUP<Buffer>               (*m_Context);
            case RHI::ERHI::CmdList:          return CreateUP<CmdList>              (*m_Context);
            case RHI::ERHI::CmdList2:         return CreateUP<CmdList2>             (*m_Context);
            default:                          NEPTUNE_LOG_CORE(E) << "Direct3D12 do not support RHI: [ " << ToString(e) << " ].";          return nullptr;
		}
	}

    std::any GraphicsBackend::AccessInfrastructure() const
    {
        return m_Context->Get<IAccessibleInfrastructures>()->GetContext();
    }
}

#endif