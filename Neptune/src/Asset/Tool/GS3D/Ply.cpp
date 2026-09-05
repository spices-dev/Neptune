/**
* @file Ply.cpp.
* @brief The Ply Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Ply.h"
#include "Asset/SOP/GS3D.h"

#define TINYPLY_IMPLEMENTATION
#include <tinyply.h>

namespace Neptune::Tool {
    
    bool Ply::Load(const std::filesystem::path& file, SOP::GS3D* obj)
    {
        NEPTUNE_PROFILE_ZONE
        
        std::ifstream stream(file, std::ios::binary);

        stream.seekg(0, std::ios::end);
        const float size = stream.tellg() * float(1e-6);
        stream.seekg(0, std::ios::beg);

        tinyply::PlyFile splat;
        splat.parse_header(stream);

        SP<tinyply::PlyData> position, normal, f_dc, f_rest, alpha, scale, orientation;

        try
        {
            position = splat.request_properties_from_element("vertex", { "x", "y", "z" });
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        try
        {
            normal = splat.request_properties_from_element("vertex", { "nx", "ny", "nz" });
        }
        catch (const std::exception& e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        try
        {
            alpha = splat.request_properties_from_element("vertex", { "opacity" });
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        try
        {
            scale = splat.request_properties_from_element("vertex", { "scale_0", "scale_1", "scale_2" });
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        try
        {
            orientation = splat.request_properties_from_element("vertex", { "rot_0", "rot_1", "rot_2", "rot_3" });
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        std::vector<std::string> sh_dc_names;
        std::vector<std::string> sh_rest_names;

        std::vector<tinyply::PlyElement> elements = splat.get_elements();
        auto vertex_element_iter = std::ranges::find_if(elements, [](const tinyply::PlyElement& e) { return e.name == "vertex"; });

        if (vertex_element_iter == elements.end()) 
        {
            NEPTUNE_LOG_CORE(E) << "no vertex element found in ply file";
            
            return false;
        }

        for (const auto & prop : vertex_element_iter->properties) 
        {
            if (prop.name.substr(0, 5) == "f_dc_")
            {
                sh_dc_names.push_back(prop.name);
            }
            else if (prop.name.substr(0, 7) == "f_rest_")
            {
                sh_rest_names.push_back(prop.name);
            }
        }
        
        try
        {
            f_dc = splat.request_properties_from_element("vertex", sh_dc_names);
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        try 
        {
            f_rest = splat.request_properties_from_element("vertex", sh_rest_names);
        }
        catch (...) 
        {
            f_rest.reset();
        }
        
        splat.read(stream);
        
        {
			auto& positions = obj->m_Desc.positions.host;
			
			positions->resize(position->count);
			
			memcpy(positions->data(), position->buffer.get(), position->buffer.size_bytes());
		}
        
        {
            auto& normals = obj->m_Desc.normals.host;
			
            normals->resize(normal->count);
			
            memcpy(normals->data(), normal->buffer.get(), normal->buffer.size_bytes());
        }
        
        /*{
            auto& colors = obj->m_Desc.colors.host;
			
            colors->resize(color->count);
			
            memcpy(colors->data(), color->buffer.get(), color->buffer.size_bytes());
        }*/
        
        {
            auto& alphas = obj->m_Desc.alphas.host;
			
            alphas->resize(alpha->count);
			
            memcpy(alphas->data(), alpha->buffer.get(), alpha->buffer.size_bytes());
        }
        
        {
            auto& scales = obj->m_Desc.scales.host;
			
            scales->resize(scale->count);
			
            memcpy(scales->data(), scale->buffer.get(), scale->buffer.size_bytes());
        }
        
        {
            auto& orientations = obj->m_Desc.orientations.host;
			
            orientations->resize(orientation->count);
			
            memcpy(orientations->data(), orientation->buffer.get(), orientation->buffer.size_bytes());
        }
        
        /*{
            auto& albedos = obj->m_Desc.albedos.host;
			
            albedos->resize(albedo->count);
			
            memcpy(albedos->data(), albedo->buffer.get(), albedo->buffer.size_bytes());
        }*/

		obj->SetEObject(EObject::Polygon);
		
		obj->CreateRHIBuffer();
        
        return true;
    }
    
}