/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/IndexBuffer.h"

namespace Neptune::Direct3D12 {

	/**
	* @brief Direct3D12::IndexBuffer Class.
	* This class defines the Direct3D12::IndexBuffer behaves.
	*/
	class IndexBuffer : public ContextAccessor, public RHI::RHIIndexBuffer::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit IndexBuffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~IndexBuffer() override = default;

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		const uint64_t& Size() const override { return 0; }

		/**
		* @brief Create Buffer.
		*
		* @param[in] size Buffer Size.
		*/
		void CreateBuffer(uint64_t size) override;

		/**
		* @brief Write host data to Buffer.
		*
		* @param[in] data Host data.
		* @param[in] size Buffer size.
		*/
		void WriteToBuffer(const void* data, uint64_t size = UINT64_MAX) override;

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		void Flush(uint64_t size = UINT64_MAX, uint64_t offset = 0) const override;
        
		/**
		* @brief Set Buffer Name.
		*
		* @param[in] name Buffer Name.
		*/
		void SetName(const std::string& name) const override;
		
	private:

	};
}

#endif