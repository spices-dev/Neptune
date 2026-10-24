/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Resource.h"

namespace Neptune::Direct3D12::Resource {
 
	/**
	* @brief Direct3D12::Buffer Class.
	* This class defines the Direct3D12::Buffer behaves.
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
		const Unit::Resource::Handle& Handle() const { return m_Buffer.GetHandle(); }

		/**
		* @brief Get Unit Handle Interface.
		* 
		* @return Returns Unit Handle Interface.
		*/
		const Unit::Resource& IHandle() const { return m_Buffer; }

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		uint64_t Size() const { return m_Size; }

		/**
		* @brief Get Buffer Host Data.
		*
		* @return Returns Buffer Host Data.
		*/
		void* Data() const { return m_HostMemory; }

		/**
		* @brief Create Buffer.
		* 
		* @param[in] desc D3D12_RESOURCE_DESC.
		* @param[in] state D3D12_RESOURCE_STATES.
		* @param[in] type D3D12_HEAP_TYPE.
		*/
		void CreateBuffer(const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, D3D12_HEAP_TYPE type);

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
		void UnapHostMemory();
		
		/**
		* @brief Get Buffer Device Address.
		*
		* @return Returns Buffer Device Address.
		*/
		D3D12_GPU_VIRTUAL_ADDRESS GetDeviceAddress() const;
		
		/**
		* @brief Set Buffer name.
		*
		* @param[in] name Buffer name.
		*/
		void SetName(const std::string& name) const;

	private:

		Unit::Resource m_Buffer;                        // @brief This Buffer.
		void*          m_HostMemory = nullptr;          // @brief Buffer Host Memory.
		uint64_t       m_Size    = 0;                   // @brief Buffer Size.
	};
}

#endif