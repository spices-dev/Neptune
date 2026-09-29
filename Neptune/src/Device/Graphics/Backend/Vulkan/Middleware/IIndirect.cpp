/**
* @file IIndirect.cpp.
* @brief The IIndirect Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "IIndirect.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DeviceAddressCommands.h"
#include "Device/Graphics/Backend/Vulkan/Extension/BufferDeviceAddress.h"
#include "Device/Graphics/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Device/Graphics/Backend/Vulkan/RHI/Buffer.h"

namespace Neptune::Vulkan::Middleware {
	
    UP<IIndirect> IIndirect::Create(const Context& context)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (context.Get<IExtensions>()->GetContext()->Has<Extension::IDeviceAddressCommands>() && context.Get<IExtensions>()->GetContext()->Has<Extension::IBufferDeviceAddress>())
        {
            return CreateUP<Indirect2>();
        }

        return CreateUP<Indirect>();
    }
    
    void Indirect::CmdDispatchIndirect(const SP<Unit::CommandBuffer>& commandBuffer, const Buffer* buffer, uint64_t offset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        commandBuffer->DispatchIndirect(buffer->Handle(), offset);
    }
    
    void Indirect2::CmdDispatchIndirect(const SP<Unit::CommandBuffer>& commandBuffer, const Buffer* buffer, uint64_t offset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        VkDispatchIndirect2InfoKHR       info{};
        info.sType                     = VK_STRUCTURE_TYPE_DISPATCH_INDIRECT_2_INFO_KHR;
        info.addressFlags              = 0;
        info.addressRange.address      = buffer->GetDeviceAddress() + offset;
        info.addressRange.size         = sizeof(VkDispatchIndirectCommand);
        
        commandBuffer->DispatchIndirect2(info);
    }
}

#endif