/**
* @file HDR.h.
* @brief The HDR Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"
#include "Device/Graphics/Frontend/Enum.h"

namespace Neptune::Vulkan::Extension {

    using IHDR = IExtension<class HDR, EExtension::HDR>;
    
    class HDR : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit HDR(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~HDR() override = default;
        
        /**
        * @brief Get HDR Surface.
        * 
        * @param[in] surface Graphic::EHDRSurface.
        * 
        * @return Returns VkSurfaceFormatKHR.
        */
        const VkSurfaceFormatKHR& GetFormat(Graphic::EHDRSurface surface) const { return m_Formats.at(surface); }
        
        /**
        * @brief Is Device Surface Formats satisfied.
        * 
        * @param[in] formats VkSurfaceFormatKHR.
        * 
        * @return Returns true if satisfied.
        */
        bool IsSurfaceFormatsSatisfied(const std::vector<VkSurfaceFormatKHR>& formats) override;
        
    private:
        
        std::unordered_map<Graphic::EHDRSurface, VkSurfaceFormatKHR> m_Formats;
    };
}

#endif