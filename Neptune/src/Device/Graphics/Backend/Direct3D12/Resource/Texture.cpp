/**
* @file Texture.cpp.
* @brief The Texture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Texture.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"

namespace Neptune::Direct3D12::Resource {

    void Texture::SetTexture(Unit::Resource::Handle texture)
    {
        NEPTUNE_PROFILE_ZONE

        m_Texture.SetHandle(texture);

        DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
    }
    
    void Texture::CreateTexture(const D3D12_RESOURCE_DESC& desc)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Format                     = desc.Format;
        m_LayerCount                 = desc.DepthOrArraySize;
        m_Width                      = static_cast<uint32_t>(desc.Width);
        m_Height                     = static_cast<uint32_t>(desc.Height);
		 
        m_Texture.CreateCommittedResource(GetContext().Get<IDevice>()->Handle(), desc, D3D12_RESOURCE_STATE_COMMON, D3D12_HEAP_TYPE_DEFAULT);
        
        DEBUGUTILS_SETOBJECTNAME(m_Texture, "Texture")
    }
    
    void Texture::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE

        DEBUGUTILS_SETOBJECTNAME(m_Texture,        name + "Texture")
    }
}

#endif