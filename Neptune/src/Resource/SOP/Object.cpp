/**
* @file Object.cpp.
* @brief The Object Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Object.h"
#include "Loader.h"

namespace Neptune::SOP {
    
    bool Object::Load()
    {
        NEPTUNE_PROFILE_ZONE
        
        return Loader::Load(FilePath(), this);
    }
    
}