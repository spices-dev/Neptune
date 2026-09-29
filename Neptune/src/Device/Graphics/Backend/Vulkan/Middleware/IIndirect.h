/**
* @file IIndirect.h.
* @brief The IIndirect Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Unit {
	
	class CommandBuffer;
}

namespace Neptune::Vulkan {
	
	class Buffer;
}

namespace Neptune::Vulkan::Middleware {
	
    /**
    * @brief Interface of IIndirect.
    */
    class IIndirect
    {
    public:
		
        /**
        * @brief Create IIndirect.
        * 
        * @param context Context.
        * 
        * @return Returns IIndirect.
        */
        static UP<IIndirect> Create(const Context& context);
		
        /**
        * @brief Destructor Function.
        */
        virtual ~IIndirect() = default;
    	
    	/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] buffer Buffer.
		* @param[in] offset .
		*/
    	virtual void CmdDispatchIndirect(const SP<Unit::CommandBuffer>& commandBuffer, const Buffer* buffer, uint64_t offset) const = 0;
    };
	
	/**
	* @brief Implement of Indirect.
	*/
	class Indirect : public IIndirect
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Indirect() = default;

		/**
		* @brief Destructor Function.
		*/
		~Indirect() override = default;
		
		/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] buffer Buffer.
		* @param[in] offset .
		*/
		void CmdDispatchIndirect(const SP<Unit::CommandBuffer>& commandBuffer, const Buffer* buffer, uint64_t offset) const override;
	};
	
	/**
	* @brief Implement of Indirect2.
	*/
	class Indirect2 : public IIndirect
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Indirect2() = default;

		/**
		* @brief Destructor Function.
		*/
		~Indirect2() override = default;
		
		/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] buffer Buffer.
		* @param[in] offset .
		*/
		void CmdDispatchIndirect(const SP<Unit::CommandBuffer>& commandBuffer, const Buffer* buffer, uint64_t offset) const override;
	};
}

#endif