/**
* @file DebugUtils.h.
* @brief The DebugUtils Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDebugUtils = IExtension<class DebugUtils, EExtension::DebugUtils>;
    
    class DebugUtils : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        DebugUtils();
        
        /**
        * @brief Destructor Function.
        */
        ~DebugUtils() override = default;
        
        /**
        * @brief Get Validation Features.
        * 
        * @return Returns Validation Features.
        */
        const std::vector<VkValidationFeatureEnableEXT>& GetFeatures() const { return m_Features; }
        
    private:
        
        std::vector<VkValidationFeatureEnableEXT> m_Features;  // @brief VkValidationFeatureEnableEXT
    };
}

#endif