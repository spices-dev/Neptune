/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Buffer.h"
#include "CmdList2.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"

namespace Neptune::Vulkan {
    
    void Buffer::CreateBuffer(uint64_t size)
    {
        NEPTUNE_PROFILE_ZONE
        
        VkBufferCreateInfo                   info{};
        info.sType                         = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        info.size                          = size;
        info.usage                         = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
        info.sharingMode                   = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount         = 1;
        info.pQueueFamilyIndices           = &GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
        
        m_Buffer.CreateBuffer(info, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    }

    void Buffer::WriteToBuffer(const void* data, uint64_t size)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_StagingBuffer = CreateUP<Resource::Buffer>(GetContext());
        
        VkBufferCreateInfo                   info{};
        info.sType                         = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        info.size                          = std::min(size, m_Buffer.Size());
        info.usage                         = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        info.sharingMode                   = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount         = 1;
        info.pQueueFamilyIndices           = &GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
    
        m_StagingBuffer->CreateBuffer(info, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
    
        m_StagingBuffer->WriteToBuffer(data);
    
        m_StagingBuffer->Flush();
    }

    void Buffer::Flush(uint64_t size, uint64_t offset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        CmdList2 cmdList(GetContext());

        cmdList.SetGraphicCmdList();

        cmdList.Begin();

        VkBufferCopy                         region{};
        region.srcOffset                   = 0;
        region.dstOffset                   = offset;
        region.size                        = std::min(size, m_Buffer.Size());

        cmdList.CmdCopyBuffer(m_StagingBuffer->Handle(), m_Buffer.Handle(), region);

        cmdList.End();

        cmdList.SubmitWait();
    }
    
    uint64_t Buffer::GetDeviceAddress() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_Buffer.GetDeviceAddress();
    }
    
    void Buffer::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Buffer.SetName(name);
    }
    
}

#endif