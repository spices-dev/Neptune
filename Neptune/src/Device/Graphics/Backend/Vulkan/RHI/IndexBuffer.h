/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Resource/Buffer.h"
#include "Device/Graphics/Frontend/RHI/IndexBuffer.h"

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::IndexBuffer Class.
	* This class defines the Vulkan::IndexBuffer behaves.
	*/
	class IndexBuffer : public ContextAccessor, public RHI::RHIIndexBuffer::Impl
	{
	public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit IndexBuffer(Context& context) : ContextAccessor(context), m_Buffer(context) {}

        /**
        * @brief Destructor Function.
        */
        ~IndexBuffer() override = default;

        /**
        * @brief Get Buffer Size.
        *
        * @return Returns Buffer Size.
        */
		uint64_t Size() const override { return m_Buffer.Size(); }

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
        
	public:
		
		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Buffer::Handle& Handle() const { return m_Buffer.Handle(); }
		
    private:

        Resource::Buffer m_Buffer;                  // @brief This Buffer.
        UP<Resource::Buffer> m_StagingBuffer;       // @brief This Staging Buffer.
    };
}

#endif