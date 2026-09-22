/**
* @file WindowInterface.cpp.
* @brief The WindowInterface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WindowInterface.h"
#include "Window/Window.h"

#if defined(NP_WINDOW_GLFW) || defined(NP_WINDOW_EMSCRIPTENGLFW)
#include <backends/imgui_impl_glfw.h>
#include "GLFW/glfw3.h"
#endif

namespace Neptune::imgui {

	UP<WindowInterface> CreateWindowInterface(WindowImplement implement)
	{
		NEPTUNE_PROFILE_ZONE

		switch (implement)
		{
#ifdef NP_WINDOW_GLFW
			case WindowImplement::GLFW: return CreateUP<GLFWInterface>();
#endif
#ifdef NP_WINDOW_EMSCRIPTENGLFW
			case WindowImplement::emscripten_glfw: return CreateUP<GLFWInterface>();
#endif
			default:
			{
				NEPTUNE_LOG_CORE(C) << "Not supported WindowImplement in ImGui Slate Configuration.";
				return nullptr;
			}
		}
	}

#if defined(NP_WINDOW_GLFW) || defined(NP_WINDOW_EMSCRIPTENGLFW)
	
	void GLFWInterface::OnInitialize(RenderBackendEnum e) const
	{
		NEPTUNE_PROFILE_ZONE

		switch (e)
		{
			case RenderBackendEnum::OpenGL:
			{
				ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			case RenderBackendEnum::Vulkan:
			{
				ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			case RenderBackendEnum::Direct3D11:
			case RenderBackendEnum::Direct3D12:
			{
				ImGui_ImplGlfw_InitForOther(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			case RenderBackendEnum::Metal:
			{
				ImGui_ImplGlfw_InitForOther(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			case RenderBackendEnum::WebGL:
			case RenderBackendEnum::WebGPU:
			{
				ImGui_ImplGlfw_InitForOther(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported RenderBackendEnum in GLFWInterface::OnInitialize.";
				break;
			}
		}
	}

	void GLFWInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplGlfw_Shutdown();
	}

	void GLFWInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplGlfw_NewFrame();
	}
	
	void* GLFWInterface::Handle() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return glfwGetCurrentContext();
	}
	
	void GLFWInterface::MakeCurrent(void* window) const
	{
		NEPTUNE_PROFILE_ZONE
		
		glfwMakeContextCurrent(static_cast<GLFWwindow*>(window));
	}
	
#endif

}