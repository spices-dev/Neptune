/**
* @file GS3D.cpp.
* @brief The GS3D Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "GS3D.h"
#include "Asset/SOP/GS3D.h"
#include "Ply.h"

namespace Neptune::Tool {

    namespace {
        
        constexpr char kPly[]     = ".ply";           // @brief Ply identify.
    }
    
    bool GS3D::Load(const std::filesystem::path& file, SOP::Object* obj)
    {
        NEPTUNE_PROFILE_ZONE
        
        std::error_code ec;
		
        if (!std::filesystem::exists(file, ec)) {
			
            NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] do not exist.";
			
            return false;
        }
		
        if (std::strncmp(file.extension().string().c_str(), kPly, sizeof(kPly)) == 0)
        {
            return Ply::Load(file, static_cast<SOP::GS3D*>(obj));
        }
        
        NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] has an unknown extension: " << file.extension().string();
		
        return false;
    }
    
}