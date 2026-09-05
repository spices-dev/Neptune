/**
* @file Ply.h.
* @brief The Ply Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::SOP {
    
    class GS3D;
}

namespace Neptune::Tool {
    
    /**
    * @brief ply file Tool.
    */
    class Ply 
    {
    public:
        
        /**
        * @brief Load SOP data from external file.
        * 
        * @param[in] file mesh file path.
        * @param[in,out] obj GS3D.
        * 
        * @return Returns true if load data successfully.
        */
        static bool Load(const std::filesystem::path& file, SOP::GS3D* obj);
    };
    
}