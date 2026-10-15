/**
* @file Sog.h.
* @brief The Sog Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::SOP {
    
    class GS3D;
}

namespace Neptune {
    
    class RenderTarget;
}

namespace Neptune::Tool {
    
    /**
    * @brief Sog file Tool.
    */
    class Sog 
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
        
        static std::unordered_map<std::string, std::vector<uint8_t>> UnZip(const std::filesystem::path& file);
        
        static SP<RenderTarget> DecodeWebp(const std::vector<uint8_t>& buf);
    };
    
}