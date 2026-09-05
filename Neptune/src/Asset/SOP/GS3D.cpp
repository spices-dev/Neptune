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
        
        Update_Attribute(positions)
        Update_Attribute(colors)
        Update_Attribute(alphas)
        Update_Attribute(scales)
        Update_Attribute(orientations)
        
        Update_Attribute(sphr)
        Update_Attribute(sphg)
        Update_Attribute(sphb)
        
        Update_Attribute(normals)
        Update_Attribute(albedos)
        
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