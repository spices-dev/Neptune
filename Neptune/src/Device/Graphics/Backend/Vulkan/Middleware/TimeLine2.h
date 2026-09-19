/**
* @file TimeLine2.h.
* @brief The TimeLine2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Semaphore.h"
#include "ITimeLine.h"

namespace Neptune::Vulkan::Middleware {
	
    /**
    * @brief Implement of TimeLineSemaphore.
    */
    class TimeLine2 : public ContextAccessor, public ITimeLine
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit TimeLine2(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~TimeLine2() override = default;
		
    	/**
		* @brief Interface of Wait TimeLine.
		* 
		* @param[in] frameId Frame Id;
		*/
    	void Wait(uint64_t frameId) const override;
    	
    	/**
		* @brief Interface of Get Semaphore.
		* 
		* @return Returns VkSemaphore.
		*/
    	VkSemaphore Semaphore() const override;
        
    	/**
		* @brief Interface of Get Fence.
		* 
		* @param[in] frameId Frame Id;
		* 
		* @return Returns VkFence.
		*/
    	VkFence Fence(uint64_t frameId) const override { return VK_NULL_HANDLE; }
    	
    	/**
		* @brief Set Name.
		* 
		* @param[in] name .
		*/
    	void SetName(const std::string& name) const override;
    	
    private:
		
    	/**
		* @brief Create Fence.
		*/
    	void Create();
    	
    private:
    	
    	Unit::Semaphore m_Semaphore;    // @brief this Semaphore.
    };
}

#endif