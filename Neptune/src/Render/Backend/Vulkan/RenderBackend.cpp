/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderBackend.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Extension/TimelineSemaphore.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRendering.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Synchronization2.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/InfrastructureHeader.h"
#include "Device/Graphics/Backend/Vulkan/AInfrastructure/AccessibleInfrastructure.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderPass.h"
#include "Render/Frontend/Pass/SlatePass.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

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
			context.Get<IComputeTimelineSemaphore>()->Wait(clock.m_FrameId - MaxFrameInFlight);

			context.Get<IGraphicTimelineSemaphore>()->Wait(clock.m_FrameId - MaxFrameInFlight);
		}

		{
			if (!context.Get<ISwapChain>()->GetNextImage(context.Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex), clock.m_ImageIndex))
			{
				RecreateSwapChain();
			}
		}

		{
			VkCommandBufferBeginInfo               beginInfo{};
			beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			beginInfo.pInheritanceInfo           = nullptr;

            context.Get<IComputeCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);

            context.Get<IGraphicCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);
		}
    	
    	if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDynamicRendering>() && GetContext().Get<IExtensions>()->GetContext().Has<Extension::ISynchronization2>())
		{
			VkImageMemoryBarrier2                     barrier{};
			barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
			barrier.srcStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.srcAccessMask                   = VK_ACCESS_2_NONE;
			barrier.dstStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.dstAccessMask                   = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.oldLayout                       = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			barrier.newLayout                       = VK_IMAGE_LAYOUT_GENERAL;
			barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.image                           = GetContext().Get<ISwapChain>()->GetImage(clock.m_ImageIndex);
			barrier.subresourceRange                = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
				
			VkDependencyInfo                          info{};
			info.sType                              = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
			info.imageMemoryBarrierCount            = 1;
			info.pImageMemoryBarriers               = &barrier;
			
			context.Get<IGraphicCommandBuffer>()->IHandle(clock.m_FrameIndex)->CmdPipelineBarrier2(info);
		}
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
		NEPTUNE_PROFILE_ZONE

		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
    	
    	if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDynamicRendering>() && GetContext().Get<IExtensions>()->GetContext().Has<Extension::ISynchronization2>())
		{
			VkImageMemoryBarrier2                     barrier{};
			barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
			barrier.srcStageMask                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
			barrier.srcAccessMask                   = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
			barrier.dstStageMask                    = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
			barrier.dstAccessMask                   = VK_ACCESS_2_NONE;
			barrier.oldLayout                       = VK_IMAGE_LAYOUT_GENERAL;
			barrier.newLayout                       = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
			barrier.image                           = GetContext().Get<ISwapChain>()->GetImage(clock.m_ImageIndex);
			barrier.subresourceRange               = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
				
			VkDependencyInfo                          info{};
			info.sType                              = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
			info.imageMemoryBarrierCount            = 1;
			info.pImageMemoryBarriers               = &barrier;
			
			context.Get<IGraphicCommandBuffer>()->IHandle(clock.m_FrameIndex)->CmdPipelineBarrier2(info);
		}
	    
		{
			context.Get<IComputeCommandBuffer>()->End(clock.m_FrameIndex);

			context.Get<IGraphicCommandBuffer>()->End(clock.m_FrameIndex);
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			VkSemaphoreSubmitInfo                  signalInfo{};
			signalInfo.sType                     = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			signalInfo.stageMask                 = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
			signalInfo.semaphore                 = context.Get<IComputeTimelineSemaphore>()->Handle();
			signalInfo.value                     = clock.m_FrameId;

			VkCommandBufferSubmitInfo              commandInfo{};
			commandInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
			commandInfo.commandBuffer            = context.Get<IComputeCommandBuffer>()->Handle(clock.m_FrameIndex);

			VkSubmitInfo2                          submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
			submitInfo.waitSemaphoreInfoCount    = 0;
			submitInfo.pWaitSemaphoreInfos       = nullptr;
			submitInfo.commandBufferInfoCount    = 1;
			submitInfo.pCommandBufferInfos       = &commandInfo;
			submitInfo.signalSemaphoreInfoCount  = 1;
			submitInfo.pSignalSemaphoreInfos     = &signalInfo;

			context.Get<IComputeQueue>()->Submit2(submitInfo);

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			VkSemaphoreSubmitInfo                  waitInfo0{};
			waitInfo0.sType                      = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			waitInfo0.stageMask                  = VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT;
			waitInfo0.semaphore                  = context.Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex);
			
			VkSemaphoreSubmitInfo                  waitInfo1{};
			waitInfo1.sType                      = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			waitInfo1.stageMask                  = VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT;
			waitInfo1.semaphore                  = context.Get<IComputeTimelineSemaphore>()->Handle();
			waitInfo1.value                      = clock.m_FrameId;
			
			VkSemaphoreSubmitInfo waitInfo[]     = { waitInfo0, waitInfo1 };
			
			VkSemaphoreSubmitInfo                  signalInfo0{};
			signalInfo0.sType                    = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			signalInfo0.stageMask                = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
			signalInfo0.semaphore                = context.Get<IGraphicTimelineSemaphore>()->Handle();
			signalInfo0.value                    = clock.m_FrameId;

			VkSemaphoreSubmitInfo                  signalInfo1{};
			signalInfo1.sType                    = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
			signalInfo1.stageMask                = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
			signalInfo1.semaphore                = context.Get<IGraphicQueueSemaphore>()->Handle(clock.m_ImageIndex);
			
			VkSemaphoreSubmitInfo signalInfo[]   = { signalInfo0, signalInfo1 };
			
			VkCommandBufferSubmitInfo              commandInfo{};
			commandInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
			commandInfo.commandBuffer            = context.Get<IGraphicCommandBuffer>()->Handle(clock.m_FrameIndex);

			VkSubmitInfo2                          submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
			submitInfo.waitSemaphoreInfoCount    = 2;
			submitInfo.pWaitSemaphoreInfos       = waitInfo;
			submitInfo.commandBufferInfoCount    = 1;
			submitInfo.pCommandBufferInfos       = &commandInfo;
			submitInfo.signalSemaphoreInfoCount  = 2;
			submitInfo.pSignalSemaphoreInfos     = signalInfo;

			context.Get<IGraphicQueue>()->Submit2(submitInfo);

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
	
	std::any RenderBackend::CreateRHI(RHI::ERHI e, void* payload) const
    {
    	NEPTUNE_PROFILE_ZONE
    	
	    return m_GraphicsBackend->CreateRHI(e, payload);
    }
	
	AInfrastructures RenderBackend::AccessInfrastructure() const
	{
		NEPTUNE_PROFILE_ZONE

		auto context = AContext(m_GraphicsBackend->AccessInfrastructure());

    	auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());
    	
    	context.Registry<ASwapChainImageUsage>(VK_IMAGE_USAGE_TRANSFER_DST_BIT);

    	if (GetContext().Get<IExtensions>()->GetContext().Has<Extension::IDynamicRendering>())
    	{
    		auto& formats = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->GetColorAttachmentFormats();
		
    		VkPipelineRenderingCreateInfoKHR                      renderInfo{};
    		renderInfo.sType                                    = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
    		renderInfo.colorAttachmentCount                     = static_cast<uint32_t>(formats.size());
    		renderInfo.pColorAttachmentFormats                  = formats.data();
    		
    		context.Registry<APipelineRenderingCreateInfo>(renderInfo);
    	}
	    else
	    {
	    	context.Registry<ASwapChainRenderPass>(pass->GetRenderPass()->GetRHIImpl<RenderPass>()->Handle());
	    }
    	
		return context.GetInfrastructures();
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