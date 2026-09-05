/**
* @file GS3D.h.
* @brief The GS3D Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::SOP {
    
    class Object;
}

namespace Neptune::Tool {
    
    /**
    * @brief GS3D external file Tool.
    * Support: .ply
    */
    class GS3D 
    {
    public:
        
        /**
        * @brief Load SOP data from external file.
        * 
        * @param[in] file mesh file path.
        * @param[in,out] obj Object.
        * 
        * @return Returns true if load data successfully.
        */
        static bool Load(const std::filesystem::path& file, SOP::Object* obj);
    };
    
}