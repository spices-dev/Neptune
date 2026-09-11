/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {
	
	using RHIIndexBuffer = RHI<ERHI::IndexBuffer>;

	/**
	* @brief Specialization of RHIIndexBuffer::Impl
	*/
	template<>
	class RHIIndexBuffer::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;
		
		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		virtual uint64_t Size() const = 0;

		/**
		* @brief Create Buffer.
		* 
		* @param[in] size Buffer Size.
		*/
		virtual void CreateBuffer(uint64_t size) = 0;

		/**
		* @brief Write host data to Buffer.
		*
		* @param[in] data Host data.
		* @param[in] size Buffer size.
		*/
		virtual void WriteToBuffer(const void* data, uint64_t size = UINT64_MAX) = 0;

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		virtual void Flush(uint64_t size = UINT64_MAX, uint64_t offset = 0) const = 0;
        
		/**
		* @brief Set Buffer Name.
		*
		* @param[in] name Buffer Name.
		*/
		virtual void SetName(const std::string& name) const = 0;
	};

	/**
	* @brief RHI of ERHI::IndexBuffer
	*/
	class IndexBuffer : public RHIIndexBuffer
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		IndexBuffer() = default;

		/**
		* @brief Destructor Function.
		*/
		~IndexBuffer() override = default;

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		uint64_t Size() const { return m_Impl->Size(); }

		/**
		* @brief Create Buffer.
		* 
		* @param[in] size Buffer Size.
		*/
		void CreateBuffer(uint64_t size) const { return m_Impl->CreateBuffer(size); }

		/**
		* @brief Write host data to Buffer.
		*
		* @param[in] data Host data.
		* @param[in] size Buffer size.
		*/
		void WriteToBuffer(const void* data, uint64_t size = UINT64_MAX) const { return m_Impl->WriteToBuffer(data, size); }

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		void Flush(uint64_t size = UINT64_MAX, uint64_t offset = 0) const { return m_Impl->Flush(size, offset); }

		/**
		* @brief Set Buffer Name.
		*
		* @param[in] name Buffer Name.
		*/
		void SetName(const std::string& name) const { return m_Impl->SetName(name); }
	};
}