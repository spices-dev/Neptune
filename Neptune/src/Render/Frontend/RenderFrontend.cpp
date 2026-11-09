/**
* @file RenderFrontend.cpp.
* @brief The RenderFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontend.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"

#ifdef NP_GRAPHICS_DIRECT3D11
#include "Render/Backend/Direct3D11/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_DIRECT3D12
#include "Render/Backend/Direct3D12/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_METAL
#include "Render/Backend/Metal/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_WEBGL
#include "Render/Backend/WebGL/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_WEBGPU
#include "Render/Backend/WebGPU/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_OPENGL
#include "Render/Backend/OpenGL/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_OPENGLES
#include "Render/Backend/OpenGLES/RenderBackend.h"
#endif

#ifdef NP_GRAPHICS_VULKAN
#include "Render/Backend/Vulkan/RenderBackend.h"
#endif

#include "Render/Frontend/Pass/GS3DTileRenderPass.h"
#include "Render/Frontend/Pass/FPSPass.h"
#include "Render/Frontend/Pass/BasePass.h"
#include "Render/Frontend/Pass/SlatePass.h"
#include "Render/Frontend/Pass/PrePass.h"
#include "Render/Frontend/Pass/Pass.h"
#include "Device/Graphics/Frontend/RHI/RHI.h"
#include "Window/Window.h"
#include "Core/Event/WindowEvent.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "Resource/Shader/Shader.h"
#include "Resource/Buffer/Buffer.h"

namespace Neptune {

    UP<RenderFrontend> RenderFrontend::Create(RenderBackendEnum backend)
    {
        NEPTUNE_PROFILE_ZONE

        UP<RenderFrontend> sp = nullptr;

        switch(backend)
        {
#ifdef NP_GRAPHICS_DIRECT3D11
            case RenderBackendEnum::Direct3D11: sp = CreateUP<Direct3D11::RenderBackend>(); break;
#endif
            
#ifdef NP_GRAPHICS_DIRECT3D12
            case RenderBackendEnum::Direct3D12: sp = CreateUP<Direct3D12::RenderBackend>(); break;
#endif

#ifdef NP_GRAPHICS_METAL
            case RenderBackendEnum::Metal: sp = CreateUP<Metal::RenderBackend>(); break;
#endif

#ifdef NP_GRAPHICS_WEBGL
            case RenderBackendEnum::WebGL:  sp = CreateUP<WebGL::RenderBackend>();  break;
#endif
            
#ifdef NP_GRAPHICS_WEBGPU
            case RenderBackendEnum::WebGPU: sp = CreateUP<WebGPU::RenderBackend>(); break;
#endif
            
#ifdef NP_GRAPHICS_OPENGL
            case RenderBackendEnum::OpenGL: sp = CreateUP<OpenGL::RenderBackend>(); break;
#endif
   
#ifdef NP_GRAPHICS_OPENGLES
            case RenderBackendEnum::OpenGLES: sp = CreateUP<OpenGLES::RenderBackend>(); break;
#endif
            
#ifdef NP_GRAPHICS_VULKAN
            case RenderBackendEnum::Vulkan: sp = CreateUP<Vulkan::RenderBackend>(); break;
#endif
            
            default:
            {
                NEPTUNE_LOG_CORE(C) << "Not Supported Render Backend.";
                return nullptr;
            }
        }

        sp->OnInitialize();

        return sp;
    }

    void RenderFrontend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_CmdList = CreateSP<RHI::CmdList>();
        
        ConstructDefaultPasses();
    }

    void RenderFrontend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderPasses.clear();
        m_CmdList.reset();

        ResourcePool<RenderTarget>::Instance().Destroy();
        ResourcePool<Shader>::Instance().Destroy();
        ResourcePool<Buffer>::Instance().Destroy();
    }

    void RenderFrontend::RenderFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        std::ranges::for_each(m_RenderPasses, [&](const auto& renderPass) {
            renderPass->OnCollectRHI(scene, *m_CmdList);
        });
    }

    void RenderFrontend::RecreateSwapChain() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto extent = Window::Instance().Extent();

        WindowResizeOverEvent event(extent.x, extent.y);

        Dispatch(event);
    }

    void RenderFrontend::ConstructDefaultPasses(const glm::vec2& rtSize)
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderPasses = {};
        
        {
            auto pass = CreateSP<Render::PrePass>();
            pass->SetRTSize(rtSize);

            AddPass(pass);
        }

        {
            auto pass = CreateSP<Render::BasePass>();
            pass->SetRTSize(rtSize);

            AddPass(pass);
        }
        
        {
            auto pass = CreateSP<Render::GS3DTileRenderPass>();
            pass->SetRTSize(rtSize);

            AddPass(pass);
        }
        
        {
            auto pass = CreateSP<Render::FPSPass>();

            AddPass(pass);
        }

        {
            auto pass = CreateSP<Render::SlatePass>();

            pass->SetDelegateDrawSlate(m_RenderDelegate.onDrawSlate);
            
            AddPass(pass);
        }
    }

    void RenderFrontend::ConstructSlatePass()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderPasses.pop_back();

        auto pass = CreateSP<Render::SlatePass>();

        pass->SetDelegateDrawSlate(m_RenderDelegate.onDrawSlate);
        
        AddPass(pass);
    }

    void RenderFrontend::AddPass(SP<Render::Pass> pass)
    {
        NEPTUNE_PROFILE_ZONE

        pass->OnConstruct();

        m_RenderPasses.emplace_back(pass);
    }
}