/**
* @file HDR.cpp.
* @brief The HDR Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "HDR.h"

namespace Neptune::Vulkan::Extension {
    
    namespace {
        
        std::unordered_map<Graphic::EHDRSurface, VkSurfaceFormatKHR> s_HDRSurface = {
            { Graphic::EHDRSurface::PQ,     { VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_COLOR_SPACE_HDR10_ST2084_EXT } },
            { Graphic::EHDRSurface::HLG,    { VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_COLOR_SPACE_BT2020_LINEAR_EXT } },
            { Graphic::EHDRSurface::P3,     { VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT } },
            { Graphic::EHDRSurface::ExSRGB, { VK_FORMAT_R16G16B16A16_SFLOAT, VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT } },
        };
        
    }
    
    HDR::HDR(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddInstanceExtensions(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME);
        
        AddDeviceExtensions(VK_EXT_HDR_METADATA_EXTENSION_NAME);
    }
    
    bool HDR::IsSurfaceFormatsSatisfied(const std::vector<VkSurfaceFormatKHR>& formats)
    {
        NEPTUNE_PROFILE_ZONE
        
        for (auto& [e, hdrSurface] : s_HDRSurface)
        {
            if(!std::ranges::any_of(formats.begin(), formats.end(), [&](const auto& format) {
            
                return format.format == hdrSurface.format && format.colorSpace == hdrSurface.colorSpace;
            })) continue;
            
            m_Formats.insert({ e, hdrSurface });
        }
        
        return !m_Formats.empty();
    }
    
}

#endif
