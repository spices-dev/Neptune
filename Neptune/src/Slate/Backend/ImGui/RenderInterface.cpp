/**
* @file RenderInterface.cpp.
* @brief The RenderInterface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderInterface.h"
#include "Render/Frontend/Core.h"

#ifdef NP_GRAPHICS_OPENGL
#include "Device/Graphics/Backend/OpenGL/AInfrastructure/AccessibleInfrastructure.h"
#include <backends/imgui_impl_opengl3.h>
#endif

#ifdef NP_GRAPHICS_VULKAN
#include "Device/Graphics/Backend/Vulkan/AInfrastructure/AccessibleInfrastructure.h"
#include <backends/imgui_impl_vulkan.h>
#endif

#ifdef NP_GRAPHICS_DIRECT3D11
#include "Device/Graphics/Backend/Direct3D11/AInfrastructure/AccessibleInfrastructure.h"
#include <backends/imgui_impl_dx11.h>
#endif

#ifdef NP_GRAPHICS_DIRECT3D12
#include "Device/Graphics/Backend/Direct3D12/AInfrastructure/AccessibleInfrastructure.h"
#include <backends/imgui_impl_dx12.h>
#endif

#ifdef NP_GRAPHICS_METAL
#include "Device/Graphics/Backend/Metal/AInfrastructure/AccessibleInfrastructure.h"
#define IMGUI_IMPL_METAL_CPP
#include <backends/imgui_impl_metal.h>
#endif

#ifdef NP_GRAPHICS_WEBGPU
#include "Device/Graphics/Backend/WebGPU/AInfrastructure/AccessibleInfrastructure.h"
#include <backends/imgui_impl_wgpu.h>
#endif

namespace Neptune::imgui {

	UP<RenderInterface> CreateRenderInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
#ifdef NP_GRAPHICS_OPENGL
			case RenderBackendEnum::OpenGL: return CreateUP<OpenGLInterface>();
#endif
			
#ifdef NP_GRAPHICS_VULKAN
			case RenderBackendEnum::Vulkan: return CreateUP<VulkanInterface>();
#endif

#ifdef NP_GRAPHICS_DIRECT3D11
		case RenderBackendEnum::Direct3D11: return CreateUP<Direct3D11Interface>();
#endif
			
#ifdef NP_GRAPHICS_DIRECT3D12
		case RenderBackendEnum::Direct3D12: return CreateUP<Direct3D12Interface>();
#endif
	
#ifdef NP_GRAPHICS_METAL
		case RenderBackendEnum::Metal:      return CreateUP<MetalInterface>();
#endif
			
#ifdef NP_GRAPHICS_WEBGPU
			case RenderBackendEnum::WebGPU: return CreateUP<WebGPUInterface>();
#endif
			
			default:
			{
				NEPTUNE_LOG_CORE(C) << "Not supported RenderBackend in ImGui Slate Configuration.";
				return nullptr;
			}
		}
	}

#ifdef NP_GRAPHICS_OPENGL
	
	void OpenGLInterface::OnInitialize(const AInfrastructures& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		using namespace OpenGL;

		using enum EAccessibleInfrastructure;

		AContext context(infrastructure);
		
		ImGui_ImplOpenGL3_Init(context.Get<AApiVersionName>());
	}

	void OpenGLInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplOpenGL3_Shutdown();
	}

	void OpenGLInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplOpenGL3_NewFrame();
	}

	void OpenGLInterface::SubmitFrameRHI(void* payload) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
	
#endif
    
#ifdef NP_GRAPHICS_VULKAN
	
	void VulkanInterface::OnInitialize(const AInfrastructures& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		using namespace Vulkan;

		using enum EAccessibleInfrastructure;

		AContext context(infrastructure);

		ImGui_ImplVulkan_InitInfo                                               init_info{};
		init_info.ApiVersion                                                  = context.Get<AApiVersion>();
		init_info.Instance                                                    = context.Get<AInstance>();
		init_info.PhysicalDevice                                              = context.Get<APhysicalDevice>();
		init_info.Device                                                      = context.Get<ADevice>();
		init_info.QueueFamily                                                 = context.Get<AGraphicQueueFamily>();
		init_info.Queue                                                       = context.Get<AGraphicQueue>();
		init_info.PipelineCache                                               = VK_NULL_HANDLE;						       
		init_info.DescriptorPool                                              = context.Get<ADescriptorPool>();
		init_info.PipelineInfoMain.Subpass                                    = 0;
		init_info.PipelineInfoForViewports.SwapChainImageUsage                = context.Get<ASwapChainImageUsage>();
		init_info.MinImageCount                                               = Neptune::MaxFrameInFlight;
		init_info.ImageCount                                                  = Neptune::MaxFrameInFlight;
		init_info.PipelineInfoMain.MSAASamples                                = context.Get<AMSAASamples>();
		init_info.Allocator                                                   = context.Get<AAllocator>();
		init_info.CheckVkResultFn                                             = context.Get<ACheckResultFn>();

		if (context.Has<APipelineRenderingCreateInfo>())
		{
			init_info.UseDynamicRendering                                     = true;
			init_info.PipelineInfoMain.PipelineRenderingCreateInfo            = context.Get<APipelineRenderingCreateInfo>();
			init_info.PipelineInfoForViewports.PipelineRenderingCreateInfo    = context.Get<APipelineRenderingCreateInfo>();
		}
		else
		{
			init_info.UseDynamicRendering                                     = false;
			init_info.PipelineInfoMain.RenderPass                             = context.Get<ASwapChainRenderPass>();
		}
		
		ImGui_ImplVulkan_Init(&init_info);
	}
	
	void VulkanInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplVulkan_Shutdown();
	}

	void VulkanInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplVulkan_NewFrame();
	}

	void VulkanInterface::SubmitFrameRHI(void* payload) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), static_cast<VkCommandBuffer>(payload));

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
	
#endif

#ifdef NP_GRAPHICS_DIRECT3D11
	
	void Direct3D11Interface::OnInitialize(const AInfrastructures& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		using namespace Direct3D11;

		using enum EAccessibleInfrastructure;

		AContext context(infrastructure);
		
		const auto device = context.Get<ADevice>();
		const auto deviceContext = context.Get<ADeviceContext>();

		ImGui_ImplDX11_Init(device, deviceContext);
	}
	
	void Direct3D11Interface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplDX11_Shutdown();
	}

	void Direct3D11Interface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplDX11_NewFrame();
	}
	
	void Direct3D11Interface::SubmitFrameRHI(void* payload) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
	
#endif
    
#ifdef NP_GRAPHICS_DIRECT3D12
	
	void Direct3D12Interface::OnInitialize(const AInfrastructures& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		using namespace Direct3D12;

		using enum EAccessibleInfrastructure;

		AContext context(infrastructure);
		
		const auto CPUHandle = context.Get<ASRVCPUHandle>();
		const auto GPUHandle = context.Get<ASRVGPUHandle>();

		ImGui_ImplDX12_InitInfo                       init_info{};
		init_info.Device                            = context.Get<ADevice>();
		init_info.CommandQueue                      = context.Get<ACommandQueue>();				                                                               
		init_info.RTVFormat                         = context.Get<ARTVFormat>();
		init_info.DSVFormat                         = context.Get<ADSVFormat>();      
		init_info.SrvDescriptorHeap                 = context.Get<ASRVDescriptorHeap>();
		init_info.SrvDescriptorAllocFn              = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* , D3D12_GPU_DESCRIPTOR_HANDLE* ){};
		init_info.SrvDescriptorFreeFn               = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE){};
		init_info.LegacySingleSrvCpuDescriptor      = CPUHandle;
		init_info.LegacySingleSrvGpuDescriptor      = GPUHandle;
		init_info.NumFramesInFlight                 = Neptune::MaxFrameInFlight;	
		init_info.UserData                          = nullptr;	

		ImGui_ImplDX12_Init(&init_info);
	}
	
	void Direct3D12Interface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplDX12_Shutdown();
	}

	void Direct3D12Interface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplDX12_NewFrame();
	}
	
	void Direct3D12Interface::SubmitFrameRHI(void* payload) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const ImGuiIO& io = ImGui::GetIO();
		
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), static_cast<ID3D12GraphicsCommandList*>(payload));

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

#endif
	
#ifdef NP_GRAPHICS_METAL
	
	void MetalInterface::OnInitialize(const AInfrastructures& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		using namespace Metal;

		using enum EAccessibleInfrastructure;

		AContext context(infrastructure);

		ImGui_ImplMetal_Init(context.Get<ADevice>());
	}
	
	void MetalInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplMetal_Shutdown();
	}

	void MetalInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplMetal_NewFrame();
	}
	
	void MetalInterface::SubmitFrameRHI(void* payload) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const ImGuiIO& io = ImGui::GetIO();
		
		ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), static_cast<MTL::CommandBuffer*>(payload), nullptr);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

#endif
	
#ifdef NP_GRAPHICS_WEBGPU
	
	void WebGPUInterface::OnInitialize(const AInfrastructures& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		using namespace WebGPU;

		using enum EAccessibleInfrastructure;

		AContext context(infrastructure);
		
		ImGui_ImplWGPU_InitInfo                      init_info{};
		init_info.Device                           = context.Get<ADevice>();
		init_info.NumFramesInFlight                = Neptune::MaxFrameInFlight;
		init_info.RenderTargetFormat               = context.Get<ARTVFormat>();
		init_info.DepthStencilFormat               = context.Get<ADSVFormat>();
		
		ImGui_ImplWGPU_Init(&init_info);
	}
	
	void WebGPUInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplWGPU_Shutdown();
	}

	void WebGPUInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplWGPU_NewFrame();
	}

	void WebGPUInterface::SubmitFrameRHI(void* payload) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const ImGuiIO& io = ImGui::GetIO();
		
		ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), static_cast<WGPURenderPassEncoder>(payload));

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
	
#endif
	
}