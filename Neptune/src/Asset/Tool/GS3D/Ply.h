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

namespace tinyply {
    
    struct PlyData;
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
        
    private:
        
        /**
        * @brief Bake GSplat attribute.
        * 
        * From: Houdini22.0429 bakegsplat
        * 
        * @param[in] p One of GSplat Component Data.
        * @param[in] n One of GSplat Component Data.
        * @param[in] opacity One of GSplat Component Data.
        * @param[in] scale One of GSplat Component Data.
        * @param[in] rot One of GSplat Component Data.
        * @param[in] f_dc One of GSplat Component Data.
        * @param[in] f_rest One of GSplat Component Data.
        * @param[in,out] obj GS3D.
        * 
        * @return Returns true if succeeded.
        */
        static bool BakeGSplat(
            const SP<tinyply::PlyData>& p, 
            const SP<tinyply::PlyData>& n, 
            const SP<tinyply::PlyData>& opacity, 
            const SP<tinyply::PlyData>& scale, 
            const SP<tinyply::PlyData>& rot, 
            const SP<tinyply::PlyData>& f_dc, 
            const SP<tinyply::PlyData>& f_rest,
            SOP::GS3D* obj
        );
    };
    
}