/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Buffer.h"

namespace Neptune::WebGPU::Resource {

	/**
	* @brief WebGPU::Buffer Class.
	* This class defines the WebGPU::Buffer behaves.
	*/
	class Buffer : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Buffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Buffer() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Buffer::Handle& Handle() const { return m_Buffer.GetHandle(); }

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		uint64_t Size() const { return m_Buffer.Size(); }

		/**
		* @brief Get Buffer Host Data.
		*
		* @return Returns Buffer Host Data.
		*/
		void* Data() const { return m_Buffer.HostMemory(); }

		/**
		* @brief Create Buffer.
		* 
		* @param[in] desc WGPUBufferDescriptor.
		*/
		void CreateBuffer(const WGPUBufferDescriptor& desc);

		/**
		* @brief Write data to Buffer.
		*
		* @param[in] data .
		* @param[in] size .
		* @param[in] offset .
		*/
		void WriteToBuffer(const void* data, uint64_t size = UINT64_MAX, uint64_t offset = 0) const;
        
		/**
		* @brief Map to HostMemory.
		*/
		void MapHostMemory();
        
		/**
		* @brief Unmap from HostMemory.
		*/
		void UnapHostMemory() const;
		
		/**
		* @brief Set Buffer name.
		*
		* @param[in] name Buffer name.
		*/
		void SetName(const std::string& name) const;

	private:

		Unit::Buffer m_Buffer;       // @brief This Buffer.
	};
}

#endif