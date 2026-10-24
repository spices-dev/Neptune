/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D12/Resource/Buffer.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"

namespace Neptune::Direct3D12 {

    /**
    * @brief Direct3D12::Buffer Class.
    * This class defines the Direct3D12::Buffer behaves.
    */
    class Buffer : public ContextAccessor, public RHI::RHIBuffer::Impl
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit Buffer(Context& context) : ContextAccessor(context), m_Buffer(context) {}

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override = default;

        /**
        * @brief Get Buffer Size.
        *
        * @return Returns Buffer Size.
        */
        uint64_t Size() const override { return m_Buffer.Size(); }

        /**
        * @brief Create Buffer.
        *
        * @param[in] info BufferCreateInfo.
        */
        void CreateBuffer(const BufferCreateInfo& info) override;

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
        * @brief Get Buffer Device Address.
        *
        * @return Returns Buffer Device Address.
        */
        uint64_t GetDeviceAddress() const override;
        
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
        const Unit::Resource::Handle& Handle() const { return m_Buffer.Handle(); }
        
    private:

        Resource::Buffer m_Buffer;                  // @brief This Buffer.
        UP<Resource::Buffer> m_StagingBuffer;       // @brief This Staging Buffer.
    };
}

#endif
