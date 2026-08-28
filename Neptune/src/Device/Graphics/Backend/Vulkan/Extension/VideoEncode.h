/**
* @file VideoEncode.h.
* @brief The VideoEncode Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVideoEncode = IExtension<class VideoEncode, EExtension::VideoEncode>;
    
    class VideoEncode : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        VideoEncode();
        
        /**
        * @brief Destructor Function.
        */
        ~VideoEncode() override = default;
                
        /**
        * @brief Build Device Feature Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Build Device Queue Chain.
        * 
        * @param[in,out] chains Required Chain.
        */
        void BuildQueueChain(std::unordered_set<VkQueueFlagBits>& chains) override { chains.insert(VK_QUEUE_VIDEO_ENCODE_BIT_KHR); }
        
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