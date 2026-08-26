/**
* @file VideoDecode.h.
* @brief The VideoDecode Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVideoDecode = IExtension<class VideoDecode, EExtension::VideoDecode>;
    
    class VideoDecode : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        VideoDecode();
        
        /**
        * @brief Destructor Function.
        */
        ~VideoDecode() override = default;
        
        /**
        * @brief Build Device Feature Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Combine Device Features.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied() override;
        
    private:
        
        VkPhysicalDeviceVideoMaintenance1FeaturesKHR m_VideoMaintenance1Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR };  // @brief VideoMaintenance1Features.
    
    };
}

#endif