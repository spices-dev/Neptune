/**
* @file Object.cpp.
* @brief The Object Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Object.h"
#include "Loader.h"
#include "Asset/Core.h"

namespace Neptune::SOP {
    
    bool Object::LoadFromDisk()
    {
        NEPTUNE_PROFILE_ZONE
        
        std::error_code ec;
		
        if (!std::filesystem::exists(m_FilePath, ec)) {
			
            NEPTUNE_LOG_CORE(E) << "File: [ " << m_FilePath << " ] do not exist.";
			
            return false;
        }
        
        if (std::strncmp(m_FilePath.extension().string().c_str(), Tool::kAsset, sizeof(Tool::kAsset)) == 0)
        {
            return Loader::Load(FilePath(), this);
        }
        
        return false;
    }
    
}
