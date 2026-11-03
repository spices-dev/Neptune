/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Vulkan/Infrastructure/Infrastructure.h"
#include "Vulkan/Unit/SwapChain.h"
#include "Enum.h"

#include <vector>

namespace Neptune::Vulkan {

    using ISwapChain = IInfrastructure<class SwapChain, EInfrastructure::SwapChain>;
	
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
        
    public:
		
        UP<Unit::SwapChain>              m_SwapChain;                   // @brief SwapChain.
        std::vector<VkImage>             m_Images;                      // @brief SwapChain Images.
        VkSwapchainCreateInfoKHR         m_Info{};                      // @brief VkSwapchainCreateInfoKHR.
    };

}