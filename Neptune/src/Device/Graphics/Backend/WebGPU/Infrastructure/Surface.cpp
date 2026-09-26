/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Surface.h"
#include "Instance.h"
#include "Device.h"
#include "Adapter.h"
#include "DebugUtilsObject.h"

namespace Neptune::WebGPU {

    Surface::Surface(Context& context, EInfrastructure e, const glm::uvec2& extent)
        : Infrastructure(context, e)
        , m_SurfaceProperty{ {}, extent }
    {
        NEPTUNE_PROFILE_ZONE

        Create();

        Configure();
    }

    void Surface::Create()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUEmscriptenSurfaceSourceCanvasHTMLSelector                 htmlSelector{};
        htmlSelector.chain.sType                                    = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
        htmlSelector.chain.next                                     = nullptr;
        htmlSelector.selector                                       = { HTMLCanvas.data(), HTMLCanvas.length() };

        WGPUSurfaceDescriptor                                         desc{};
        desc.nextInChain                                            = &htmlSelector.chain;

        m_Surface.CreateSurface(GetContext().Get<IInstance>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(m_Surface, ToString())

        WEBGPU_CHECK(wgpuSurfaceGetCapabilities(m_Surface.GetHandle(), GetContext().Get<IAdapter>()->Handle(), &m_SurfaceProperty.capabilities))
    }

    void Surface::Configure() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUTextureFormat viewFormats[] = { WGPUTextureFormat_RGBA8Unorm };
        
        WGPUSurfaceConfiguration configure                          = {};
        configure.device                                            = GetContext().Get<IDevice>()->Handle();
        configure.format                                            = WGPUTextureFormat_RGBA8Unorm;
        configure.usage                                             = WGPUTextureUsage_RenderAttachment;
        configure.width                                             = m_SurfaceProperty.surfaceSize.x;
        configure.height                                            = m_SurfaceProperty.surfaceSize.y;
        configure.viewFormatCount                                   = 1;
        configure.viewFormats                                       = viewFormats;
        configure.alphaMode                                         = WGPUCompositeAlphaMode_Premultiplied;
        configure.presentMode                                       = WGPUPresentMode_Fifo;
        
        wgpuSurfaceConfigure(m_Surface.GetHandle(), &configure);
    }

    bool Surface::GetNextImage()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuSurfaceGetCurrentTexture(m_Surface.GetHandle(), &m_SurfaceTexture);

        if (m_SurfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal && m_SurfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal)
        {
            return false;
        }
        
        m_SurfaceProperty.surfaceSize.x = wgpuTextureGetWidth(m_SurfaceTexture.texture);
        m_SurfaceProperty.surfaceSize.y = wgpuTextureGetHeight(m_SurfaceTexture.texture);

        m_SurfaceView = CreateUP<Unit::TextureView>();
        
        WGPUTextureViewDescriptor        desc{};
        desc.dimension                 = WGPUTextureViewDimension_2D;
        desc.baseMipLevel              = 0;
        desc.mipLevelCount             = 1;
        desc.baseArrayLayer            = 0;
        desc.arrayLayerCount           = 1;
        desc.aspect                    = WGPUTextureAspect_Undefined;
        desc.usage                     = WGPUTextureUsage_RenderAttachment;

        m_SurfaceView->CreateTextureView(m_SurfaceTexture.texture, desc);

        DEBUGUTILS_SETOBJECTNAME(*m_SurfaceView, "SurfaceTextureView")
        
        return true;
    }

    bool Surface::Present() const
    {
        NEPTUNE_PROFILE_ZONE

        return wgpuSurfacePresent(m_Surface.GetHandle()) == WGPUStatus_Success;
    }

    void Surface::Unconfigure() const
    {
        NEPTUNE_PROFILE_ZONE

        wgpuSurfaceUnconfigure(m_Surface.GetHandle());
    }

}

#endif