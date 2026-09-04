/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "Extension/ExtensionHeader.h"
#include "Layer/LayerHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Converter.h"
#include "Extension/DeviceFault.h"
#include "Extension/MemoryBudget.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {
	
	GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::Vulkan)
    {
		NEPTUNE_PROFILE_ZONE

		HandleResultDelegate::SetHandler([&](VkResult result) {
			HandleResult(
				result, 
				GetContext().Has<IPhysicalDevice>() ? GetContext().Get<IPhysicalDevice>()->Handle() : nullptr,
				GetContext().Has<IDevice>() ? GetContext().Get<IDevice>()->Handle() : nullptr, 
				GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDeviceFault>(),
				GetContext().Get<IExtensions>()->GetContext().Has<Extension::IMemoryBudget>(),
				GetContext().Has<IFunctions>() ? GetContext().Get<IFunctions>()->vkGetDeviceFaultInfoEXT : nullptr
			); 
		});
	}

	GraphicsBackend::~GraphicsBackend() = default;

	void GraphicsBackend::OnInitialize(const Window* window)
	{
		NEPTUNE_PROFILE_ZONE
    	
		m_Context = CreateUP<Context>();

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

		m_Context->Registry<IMemoryAllocator>();
					  
		m_Context->Registry<IGraphicQueueSemaphore>(SwapChainImageCount);
		m_Context->Registry<IGraphicFence>(MaxFrameInFlight);

		m_Context->Registry<IComputeQueueSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IComputeFence>(MaxFrameInFlight);

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

	std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
		NEPTUNE_PROFILE_ZONE

		switch(e)
		{
			case RHI::ERHI::RenderPass:       return std::static_pointer_cast<RHI::RHIRenderPass::Impl>    (CreateSP<RenderPass>           (*m_Context));
			case RHI::ERHI::DescriptorList:   return std::static_pointer_cast<RHI::RHIDescriptorList::Impl>(CreateSP<DescriptorList>       (*m_Context));
			case RHI::ERHI::Pipeline:         return std::static_pointer_cast<RHI::RHIPipeline::Impl>      (CreateSP<Pipeline>             (*m_Context));
			case RHI::ERHI::Shader:           return std::static_pointer_cast<RHI::RHIShader::Impl>        (CreateSP<Shader>               (*m_Context));
			case RHI::ERHI::RenderTarget:     return std::static_pointer_cast<RHI::RHIRenderTarget::Impl>  (CreateSP<RenderTarget>         (*m_Context));
			case RHI::ERHI::VertexBuffer:     return std::static_pointer_cast<RHI::RHIVertexBuffer::Impl>  (CreateSP<VertexBuffer>         (*m_Context));
			case RHI::ERHI::Buffer:           return std::static_pointer_cast<RHI::RHIBuffer::Impl>        (CreateSP<Buffer>               (*m_Context));
			case RHI::ERHI::IndexBuffer:      return std::static_pointer_cast<RHI::RHIIndexBuffer::Impl>   (CreateSP<IndexBuffer>          (*m_Context));
			case RHI::ERHI::CmdList:          return std::static_pointer_cast<RHI::RHICmdList::Impl>       (CreateSP<CmdList>              (*m_Context));
			case RHI::ERHI::CmdList2:         return std::static_pointer_cast<RHI::RHICmdList2::Impl>      (CreateSP<CmdList2>             (*m_Context));
			case RHI::ERHI::Decoder:          return std::static_pointer_cast<RHI::RHIDecoder::Impl>       (Decoder::Create                (*m_Context, payload));
			case RHI::ERHI::OpticalFlow:      return std::static_pointer_cast<RHI::RHIOpticalFlow::Impl>   (CreateSP<OpticalFlowSession>   (*m_Context));
			default:                          NEPTUNE_LOG_CORE(E) << "Vulkan do not support this RHI.";          return nullptr;
		}
	}

	AInfrastructures GraphicsBackend::AccessInfrastructure() const
	{
		NEPTUNE_PROFILE_ZONE

		AContext context;

		context.Registry<AInstance>(m_Context->Get<IInstance>()->Handle());
		context.Registry<APhysicalDevice>(m_Context->Get<IPhysicalDevice>()->Handle());
		context.Registry<ADevice>(m_Context->Get<IDevice>()->Handle());
		context.Registry<AGraphicQueueFamily>(m_Context->Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT));
		context.Registry<AGraphicQueue>(m_Context->Get<IGraphicQueue>()->Handle());
		context.Registry<ADescriptorPool>(m_Context->Get<IDescriptorPool>()->Handle());
		context.Registry<AMSAASamples>(VK_SAMPLE_COUNT_1_BIT);
		context.Registry<AAllocator>(GetAllocator());
		context.Registry<ACheckResultFn>(+[](VkResult result) { std::invoke(HandleResultDelegate::GetHandler(), result); });

		return context.GetInfrastructures();
	}

}

#endif