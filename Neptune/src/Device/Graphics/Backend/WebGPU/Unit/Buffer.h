/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::Buffer Class.
    * This class defines the WebGPU::Unit::Buffer behaves.
    */
    class Buffer : public Unit<WGPUBuffer>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Buffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override;

        /**
        * @brief Create Buffer.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUBufferDescriptor.
        */
        void CreateBuffer(WGPUDevice device, const WGPUBufferDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
        /**
        * @brief Get Buffer size.
        * 
        * @return Returns Buffer size.
        */
        uint64_t Size() const { return m_Size; }
        
        /**
        * @brief Write data to Buffer.
        *
        * @param[in] data .
        * @param[in] size .
        * @param[in] offset .
        */
        void WriteToBuffer(const void* data, uint64_t size = UINT64_MAX, uint64_t offset = 0) const;
        
    private:
        
        uint64_t m_Size = 0;              // @brief Size.
        void*    m_HostMemory = nullptr;  // @brief HostMemory.
        
    };
}

#endif