/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GraphicsBackend.h"
#include "Extension/ExtensionHeader.h"
#include "Layer/LayerHeader.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Converter.h"
#include "Extension/DeviceFault.h"
#include "Extension/MemoryBudget.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {
	
	GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::Vulkan)
    {
		NEPTUNE_PROFILE_ZONE

		HandleResultDelegate::SetHandler([&](VkResult result) {
			HandleResult(
				result, 
				GetContext().Has<IPhysicalDevice>() ? GetContext().Get<IPhysicalDevice>()->Handle() : nullptr,
				GetContext().Has<IDevice>() ? GetContext().Get<IDevice>()->Handle() : nullptr, 
				GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IDeviceFault>(),
				GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IMemoryBudget>()
			); 
		});
	}

	GraphicsBackend::~GraphicsBackend() = default;

	void GraphicsBackend::OnInitialize(const Window* window)
	{
		NEPTUNE_PROFILE_ZONE
    	
		m_Context = CreateUP<Context>();

		m_Context->Registry<IFunctions>();
		m_Context->Registry<ILayers>();
		m_Context->Registry<IExtensions>(window);
		m_Context->Registry<IInstance>();
		m_Context->Registry<IDebugUtilsObject>();
		if (window)
		{
			m_Context->Registry<ISurface>(window->Implement(), window->NativeWindow());
		}
		m_Context->Registry<IPhysicalDevice>();
		m_Context->Registry<IDevice>();

		if (m_Context->Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->HasPresentQueueFamily())
		{
			m_Context->Registry<IPresentQueue>();
		}
		if (m_Context->Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->HasQueueFamily(VK_QUEUE_GRAPHICS_BIT))
		{
			m_Context->Registry<IGraphicQueue>();
			m_Context->Registry<IGraphicThreadQueue>();
		}
		if (m_Context->Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->HasQueueFamily(VK_QUEUE_COMPUTE_BIT))
		{
			m_Context->Registry<IComputeQueue>();
			m_Context->Registry<IComputeThreadQueue>();
		}
		if (m_Context->Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->HasQueueFamily(VK_QUEUE_TRANSFER_BIT))
		{
			m_Context->Registry<ITransferThreadQueue>();
		}
		if (m_Context->Get<IExtensions>()->GetContext()->Has<Extension::IVideoDecode>())
		{
			m_Context->Registry<IVideoDecodeThreadQueue>();
		}
		if (m_Context->Get<IExtensions>()->GetContext()->Has<Extension::IVideoEncode>())
		{
			m_Context->Registry<IVideoEncodeThreadQueue>();
		}
		if (m_Context->Get<IExtensions>()->GetContext()->Has<Extension::IOpticalFlow>())
		{
			m_Context->Registry<IOpticalFlowThreadQueue>();
		}
		
		m_Context->Registry<IMemoryAllocator>();

		m_Context->Registry<IGraphicTimeLine>(MaxFrameInFlight);
		m_Context->Registry<IComputeTimeLine>(MaxFrameInFlight);
		
		m_Context->Registry<IGraphicQueueSemaphore>(SwapChainImageCount);

		m_Context->Registry<IGraphicCommandPool>();
		m_Context->Registry<IGraphicCommandBuffer>(MaxFrameInFlight);

		m_Context->Registry<IComputeCommandPool>();
		m_Context->Registry<IComputeCommandBuffer>(MaxFrameInFlight);

		m_Context->Registry<IDescriptorPool>();

		m_Context->Registry<IGraphicThreadCommandPool>();
		m_Context->Registry<IComputeThreadCommandPool>();
		m_Context->Registry<ITransferThreadCommandPool>();
		m_Context->Registry<IVideoEncodeThreadCommandPool>();
		m_Context->Registry<IVideoDecodeThreadCommandPool>();
		m_Context->Registry<IOpticalFlowThreadCommandPool>();
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

		m_Context->Get<IDevice>()->Wait();
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
			case RHI::ERHI::VertexBuffer:     return CreateUP<VertexBuffer>         (*m_Context);
			case RHI::ERHI::Buffer:           return CreateUP<Buffer>               (*m_Context);
			case RHI::ERHI::IndexBuffer:      return CreateUP<IndexBuffer>          (*m_Context);
			case RHI::ERHI::CmdList:          return CreateUP<CmdList>              (*m_Context);
			case RHI::ERHI::CmdList2:         return CreateUP<CmdList2>             (*m_Context);
			case RHI::ERHI::Decoder:          return Decoder::Create                (*m_Context, payload);
			case RHI::ERHI::OpticalFlow:      return CreateUP<OpticalFlowSession>   (*m_Context);
			default:                          NEPTUNE_LOG_CORE(E) << "Vulkan do not support RHI: [ " << ToString(e) << " ].";         return nullptr;
		}
	}

	std::any GraphicsBackend::AccessInfrastructure() const
	{
		NEPTUNE_PROFILE_ZONE

		AContext context;

		context.Registry<AInstance>            (m_Context->Get<IInstance>()->Handle());
		context.Registry<AApiVersion>          (m_Context->Get<IInstance>()->GetApiVersion());
		context.Registry<APhysicalDevice>      (m_Context->Get<IPhysicalDevice>()->Handle());
		context.Registry<ADevice>              (m_Context->Get<IDevice>()->Handle());
		context.Registry<AGraphicQueueFamily>  (m_Context->Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT));
		context.Registry<AGraphicQueue>        (m_Context->Get<IGraphicQueue>()->Handle());
		context.Registry<ADescriptorPool>      (m_Context->Get<IDescriptorPool>()->Handle());
		context.Registry<AMSAASamples>         (VK_SAMPLE_COUNT_1_BIT);
		context.Registry<AAllocator>           (GetAllocator());
		context.Registry<ACheckResultFn>       (+[](VkResult result) { std::invoke(HandleResultDelegate::GetHandler(), result); });

		return context;
	}

}

#endif