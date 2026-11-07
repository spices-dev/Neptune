/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Vulkan/Infrastructure/Infrastructure.h"
#include "Vulkan/Unit/SwapChain.h"
#include "Vulkan/Resource/Buffer.h"
#include "Enum.h"

#include <vector>

namespace Neptune::Vulkan {

    using ISwapChain = IInfrastructure<MultiInstance<VkSwapchainKHR, class SwapChain>, EInfrastructure::SwapChain>;
	
    /**
    * @brief Vulkan::SwapChain Class.
    * This class defines the Vulkan::SwapChain behaves.
    */
    class SwapChain : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        */
        SwapChain() = default;

        /**
        * @brief Destructor Function.
        */
        ~SwapChain() override = default;
        
        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::SwapChain::Handle& Handle() const { return m_SwapChain->GetHandle(); }
        
    public:
		
        UP<Unit::SwapChain>              m_SwapChain;                   // @brief SwapChain.
        UP<Resource::Buffer>             m_StagingBuffer;               // @brief StagingBuffer.
        std::vector<VkImage>             m_Images;                      // @brief SwapChain Images.
        VkSwapchainCreateInfoKHR         m_Info{};                      // @brief VkSwapchainCreateInfoKHR.
        uint32_t                         m_Family;                      // @brief Queue Family.
    };

}