/**
* @file GS3D.cpp.
* @brief The GS3D Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "GS3D.h"
#include "Asset/Tool/GS3D/GS3D.h"

namespace Neptune::SOP
{
    void GS3DDesc::UploadToDevice()
    {
        NEPTUNE_PROFILE_ZONE
        
        Update_Attribute(meansRanges)
        Update_Attribute(scaleCodes)
        Update_Attribute(sh0Codes)
        
        Update_Texture(means0, 0)
        Update_Texture(means1, 1)
        Update_Texture(scales, 2)
        Update_Texture(quats,  3)
        Update_Texture(sh0,    4)
        
        DescBase::UploadToDevice();
    }
    
    bool GS3D::LoadFromDisk()
    {
        NEPTUNE_PROFILE_ZONE
        
        if (Object::LoadFromDisk())
        {
            return true;
        }
        
        return Tool::GS3D::Load(FilePath(), this);
    }
    
    void GS3D::CreateRHIBuffer()
    {
        NEPTUNE_PROFILE_ZONE

        m_Desc.UploadToDevice();
    }
}