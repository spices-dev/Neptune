/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderBackend.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/InfrastructureHeader.h"
#include "Device/Graphics/Backend/Vulkan/AInfrastructure/AccessibleInfrastructure.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderPass.h"
#include "Render/Frontend/Pass/SlatePass.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IRenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"

namespace Neptune::Vulkan {
	
    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Vulkan)
		, m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

	void RenderBackend::OnInitialize()
	{
		NEPTUNE_PROFILE_ZONE
    	
		const auto& window = Window::Instance();

    	m_GraphicsBackend->OnInitialize(&window);
		
		GetContext().Registry<ISwapChain>(SwapChainImageCount);

		GetContext().Registry<IGraphicImageSemaphore>(MaxFrameInFlight);

		RenderFrontend::OnInitialize();
	}

	void RenderBackend::OnShutDown()
	{
		NEPTUNE_PROFILE_ZONE

		RenderFrontend::OnShutDown();

    	m_GraphicsBackend->OnShutDown();
	}
	
    void RenderBackend::BeginFrame(Scene* scene) const
    {
		NEPTUNE_PROFILE_ZONE

		auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
    	
    	if (clock.m_FrameId > MaxFrameInFlight)
		{
			context.Get<IComputeTimeLine>()->Wait(clock.m_FrameId - MaxFrameInFlight);

			context.Get<IGraphicTimeLine>()->Wait(clock.m_FrameId - MaxFrameInFlight);
		}

		{
			if (!context.Get<ISwapChain>()->GetNextImage(context.Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameId), clock.m_ImageIndex))
			{
				RecreateSwapChain();
			}
		}

		{
			VkCommandBufferBeginInfo               beginInfo{};
			beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			beginInfo.pInheritanceInfo           = nullptr;

            context.Get<IComputeCommandBuffer>()->Begin(beginInfo, clock.m_FrameId);

            context.Get<IGraphicCommandBuffer>()->Begin(beginInfo, clock.m_FrameId);
		}
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
		NEPTUNE_PROFILE_ZONE

		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
	    
		{
			context.Get<IComputeCommandBuffer>()->End(clock.m_FrameId);

			context.Get<IGraphicCommandBuffer>()->End(clock.m_FrameId);
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			VkSemaphoreSubmitInfo                  waitInfo0{};
			
			if (clock.m_FrameId > MaxFrameInFlight)
			{
				waitInfo0.sType                  = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
				waitInfo0.stageMask              = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
				waitInfo0.semaphore              = context.Get<IGraphicTimeLine>()->Semaphore(clock.m_FrameId- MaxFrameInFlight);
                waitInfo0.value                  = clock.m_FrameId - MaxFrameInFlight;
			}
			
			VkSemaphoreSubmitInfo                  signalInfo{};
			signalInfo.sType                     = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			signalInfo.stageMask                 = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
			signalInfo.semaphore                 = context.Get<IComputeTimeLine>()->Semaphore(clock.m_FrameId);
			signalInfo.value                     = clock.m_FrameId;

			VkCommandBufferSubmitInfo              commandInfo{};
			commandInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
			commandInfo.commandBuffer            = context.Get<IComputeCommandBuffer>()->Handle(clock.m_FrameId);

			VkSubmitInfo2                          submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
			submitInfo.waitSemaphoreInfoCount    = waitInfo0.semaphore ? 1 : 0;
			submitInfo.pWaitSemaphoreInfos       = waitInfo0.semaphore ? &waitInfo0 : nullptr;
			submitInfo.commandBufferInfoCount    = 1;
			submitInfo.pCommandBufferInfos       = &commandInfo;
			submitInfo.signalSemaphoreInfoCount  = 1;
			submitInfo.pSignalSemaphoreInfos     = &signalInfo;

			context.Get<IComputeQueue>()->Submit(submitInfo, context.Get<IComputeTimeLine>()->Fence(clock.m_FrameId));

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			VkSemaphoreSubmitInfo                  waitInfo0{};
			waitInfo0.sType                      = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			waitInfo0.stageMask                  = VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT;
			waitInfo0.semaphore                  = context.Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameId);
			
			VkSemaphoreSubmitInfo                  waitInfo1{};
			waitInfo1.sType                      = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			waitInfo1.stageMask                  = VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT;
			waitInfo1.semaphore                  = context.Get<IComputeTimeLine>()->Semaphore(clock.m_FrameId);
			waitInfo1.value                      = clock.m_FrameId;
			
			VkSemaphoreSubmitInfo waitInfo[]     = { waitInfo0, waitInfo1 };
			
			VkSemaphoreSubmitInfo                  signalInfo0{};
			signalInfo0.sType                    = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			signalInfo0.stageMask                = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
			signalInfo0.semaphore                = context.Get<IGraphicTimeLine>()->Semaphore(clock.m_FrameId);
			signalInfo0.value                    = clock.m_FrameId;

			VkSemaphoreSubmitInfo                  signalInfo1{};
			signalInfo1.sType                    = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			signalInfo1.stageMask                = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
			signalInfo1.semaphore                = context.Get<IGraphicQueueSemaphore>()->Handle(clock.m_ImageIndex);
			
			VkSemaphoreSubmitInfo signalInfo[]   = { signalInfo0, signalInfo1 };
			
			VkCommandBufferSubmitInfo              commandInfo{};
			commandInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
			commandInfo.commandBuffer            = context.Get<IGraphicCommandBuffer>()->Handle(clock.m_FrameId);

			VkSubmitInfo2                          submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
			submitInfo.waitSemaphoreInfoCount    = 2;
			submitInfo.pWaitSemaphoreInfos       = waitInfo;
			submitInfo.commandBufferInfoCount    = 1;
			submitInfo.pCommandBufferInfos       = &commandInfo;
			submitInfo.signalSemaphoreInfoCount  = 2;
			submitInfo.pSignalSemaphoreInfos     = signalInfo;

			context.Get<IGraphicQueue>()->Submit(submitInfo, context.Get<IGraphicTimeLine>()->Fence(clock.m_FrameId));

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IPresentQueue>()->Handle(), "PresentQueue")

			VkPresentInfoKHR                       presentInfo{};
			presentInfo.sType                    = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount       = 1;
			presentInfo.pWaitSemaphores          = &context.Get<IGraphicQueueSemaphore>()->Handle(clock.m_ImageIndex);
			presentInfo.swapchainCount           = 1;
			presentInfo.pImageIndices            = &clock.m_ImageIndex;
			presentInfo.pResults                 = nullptr;

			if (!context.Get<ISwapChain>()->Present(presentInfo))
			{
				RecreateSwapChain();
			}

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IPresentQueue>()->Handle())
		}
    }

	void RenderBackend::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		m_GraphicsBackend->Wait();
	}

	GraphicsBackend::Context& RenderBackend::GetContext() const
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	return m_GraphicsBackend->GetContext();
    }
	
	UP<RHI::RHIImplEmpty> RenderBackend::CreateRHI(RHI::ERHI e, void* payload) const
    {
    	NEPTUNE_PROFILE_ZONE
    	
	    return m_GraphicsBackend->CreateRHI(e, payload);
    }
	
	std::any RenderBackend::AccessInfrastructure() const
	{
		NEPTUNE_PROFILE_ZONE

		auto context = std::any_cast<AContext>(m_GraphicsBackend->AccessInfrastructure());

    	auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());
    	
    	context.Registry<ASwapChainImageUsage>(VK_IMAGE_USAGE_TRANSFER_DST_BIT);

		if (auto info = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->GetMiddleware()->GetRenderingInfo())
		{
			context.Registry<APipelineRenderingCreateInfo>(*info);
		}
		else if (auto handle = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->GetMiddleware()->Handle())
		{
			context.Registry<ASwapChainRenderPass>(handle);
		}
    	
		return context;
	}

	void RenderBackend::RecreateSwapChain() const
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Get<IGraphicQueue>()->Wait();

		GetContext().Registry<ISwapChain>(SwapChainImageCount, GetContext().Get<ISwapChain>()->Handle());

		RenderFrontend::RecreateSwapChain();
	}
	
}

#endif
