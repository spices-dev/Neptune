/**
* @file Buffer.h.
* @brief The Buffer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Device/Graphics/Frontend/Enum.h"

namespace Neptune::RHI {
	
    using RHIBuffer = RHI<ERHI::Buffer>;

    /**
    * @brief Specialization of RHIBuffer::Impl
    */
    template<>
    class RHIBuffer::Impl
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
        * @param[in] usage Graphic::EBufferUsage.
        */
        virtual void CreateBuffer(uint64_t size, Graphic::EBufferUsage usage = Graphic::EBufferUsage::None) = 0;

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
        * @brief Get Buffer Device Address.
        *
        * @return Returns Buffer Device Address.
        */
        virtual uint64_t GetDeviceAddress() const = 0;
        
        /**
        * @brief Set Buffer Name.
        *
        * @param[in] name Buffer Name.
        */
        virtual void SetName(const std::string& name) const = 0;
    };

    /**
    * @brief RHI of ERHI::Buffer
    */
    class Buffer : public RHIBuffer
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Buffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override = default;
        
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
        * @param[in] usage Graphic::EBufferUsage.
        */
        void CreateBuffer(uint64_t size, Graphic::EBufferUsage usage = Graphic::EBufferUsage::None) const { return m_Impl->CreateBuffer(size, usage); }

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
        * @brief Get Buffer Device Address.
        *
        * @return Returns Buffer Device Address.
        */
        uint64_t GetDeviceAddress() const { return m_Impl->GetDeviceAddress(); }

        /**
        * @brief Set Buffer Name.
        *
        * @param[in] name Buffer Name.
        */
        void SetName(const std::string& name) const { return m_Impl->SetName(name); }
    };
}