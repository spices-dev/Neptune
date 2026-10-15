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
        
        std::error_code ec;
		
        if (!std::filesystem::exists(file, ec)) {
			
            NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] do not exist.";
			
            return false;
        }
        
        std::ifstream stream(file, std::ios::binary);

        stream.seekg(0, std::ios::end);
        
        if (stream.tellg() <= 0)
        {
            NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] size error.";
			
            return false;
        }
        
        stream.seekg(0, std::ios::beg);

        tinyply::PlyFile splat;
        
        try
        {
            splat.parse_header(stream);
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply parse_header: " << e.what();
            
            return false;
        }

        SP<tinyply::PlyData> p, n, opacity, scale, rot, f_dc, f_rest;

        try
        {
            p = splat.request_properties_from_element("vertex", { "x", "y", "z" });
        }
        catch (const std::exception & e)
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }

        try
        {
            n = splat.request_properties_from_element("vertex", { "nx", "ny", "nz" });
        }
        catch (const std::exception& e)
        {
            NEPTUNE_LOG_CORE(W) << "tinyply exception: " << e.what();
        }

        try
        {
            opacity = splat.request_properties_from_element("vertex", { "opacity" });
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
            rot = splat.request_properties_from_element("vertex", { "rot_0", "rot_1", "rot_2", "rot_3" });
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
        catch (const std::exception & e) 
        {
            NEPTUNE_LOG_CORE(E) << "tinyply exception: " << e.what();
            
            return false;
        }
        
        splat.read(stream);
        
        if (!BakeGSplat(p, n, opacity, scale, rot, f_dc, f_rest, obj))
        {
            NEPTUNE_LOG_CORE(E) << "BakeGSplat failed.";

            return false;
        }

		obj->SetEObject(EObject::GS3D);
		
		obj->CreateRHIBuffer();
        
        return true;
    }
    
    bool Ply::BakeGSplat(
        const SP<tinyply::PlyData>& p, 
        const SP<tinyply::PlyData>& n, 
        const SP<tinyply::PlyData>& opacity, 
        const SP<tinyply::PlyData>& scale, 
        const SP<tinyply::PlyData>& rot, 
        const SP<tinyply::PlyData>& f_dc, 
        const SP<tinyply::PlyData>& f_rest,
        SOP::GS3D* obj
    ) {
        NEPTUNE_PROFILE_ZONE
        
        /*{
            auto& positions = obj->m_Desc.positions.host;
			
            positions->resize(p->count);
			
            memcpy(positions->data(), p->buffer.get(), p->buffer.size_bytes());
        }
        
        {
            auto addr = f_dc->buffer.get();
            
            static constexpr float SH_C0 = 0.28209479177387814f;
            
            auto& colors = obj->m_Desc.colors.host;
            
            colors->resize(f_dc->count);
            
            for (uint64_t i = 0; i < f_dc->count; ++i)
            {
                auto r = *reinterpret_cast<float*>(addr + 12 * i) * SH_C0 + 0.5f;
                auto g = *reinterpret_cast<float*>(addr + 12 * i + 4) * SH_C0 + 0.5f;
                auto b = *reinterpret_cast<float*>(addr + 12 * i + 8) * SH_C0 + 0.5f;
                
                (*colors)[i] = { r, g, b };
            }
        }
        
        {
            auto addr = opacity->buffer.get();
                            
            auto& alphas = obj->m_Desc.alphas.host;
                            
            alphas->resize(opacity->count);
                            
            for (uint64_t i = 0; i < opacity->count; ++i)
            {
                auto r = *reinterpret_cast<float*>(addr + 4 * i);
                                
                (*alphas)[i] = 1 / (1 + glm::exp(-r));
            }
        }

        {
            auto addr = scale->buffer.get();
                                            
            auto& scales = obj->m_Desc.scales.host;
                                            
            scales->resize(scale->count);
                                            
            for (uint64_t i = 0; i < scale->count; ++i)
            {
                auto r = glm::exp(*reinterpret_cast<float*>(addr + 12 * i));
                auto g = glm::exp(*reinterpret_cast<float*>(addr + 12 * i + 4));
                auto b = glm::exp(*reinterpret_cast<float*>(addr + 12 * i + 8));
                                                
                (*scales)[i] = { r, g, b };
            }
        }

        {
            auto addr = rot->buffer.get();
                    
            auto& orientations = obj->m_Desc.orientations.host;
                    
            orientations->resize(rot->count);
                    
            for (uint64_t i = 0; i < rot->count; ++i)
            {
                auto w = *reinterpret_cast<float*>(addr + 16 * i);
                auto r = *reinterpret_cast<float*>(addr + 16 * i + 4);
                auto g = *reinterpret_cast<float*>(addr + 16 * i + 8);
                auto b = *reinterpret_cast<float*>(addr + 16 * i + 12);
                        
                (*orientations)[i] = glm::normalize(glm::vec4{ r, g, b, w });
            }
        }
        
        {
            auto addr = f_rest->buffer.get();
                                          
            auto f_dc_addr = f_dc->buffer.get();
            
            auto& sphr = obj->m_Desc.sphrs.host;
                                            
            sphr->resize(f_rest->count);
                                            
            for (uint64_t i = 0; i < f_rest->count; ++i)
            {
                auto rest_0 = addr + 180 * i;
                                                
                auto r = *reinterpret_cast<float*>(f_dc_addr + 12 * i);
                
                (*sphr)[i][0][0] = r;
                
                memcpy(reinterpret_cast<char*>(sphr->data()) + 64 * i + 4, rest_0, 60);
            }
        }
        
        {
            auto addr = f_rest->buffer.get();
                                          
            auto f_dc_addr = f_dc->buffer.get();
            
            auto& sphg = obj->m_Desc.sphgs.host;
                                            
            sphg->resize(f_rest->count);
                                            
            for (uint64_t i = 0; i < f_rest->count; ++i)
            {
                auto rest_15 = addr + 180 * i + 60;
                     
                auto g = *reinterpret_cast<float*>(f_dc_addr + 12 * i + 4);
                
                (*sphg)[i][0][0] = g;
                
                memcpy(reinterpret_cast<char*>(sphg->data()) + 64 * i + 4, rest_15, 60);
            }
        }
        
        {
            auto addr = f_rest->buffer.get();
                                          
            auto f_dc_addr = f_dc->buffer.get();
            
            auto& sphb = obj->m_Desc.sphbs.host;
                                            
            sphb->resize(f_rest->count);
                                            
            for (uint64_t i = 0; i < f_rest->count; ++i)
            {
                auto rest_30 = addr + 180 * i + 120;
                 
                auto b = *reinterpret_cast<float*>(f_dc_addr + 12 * i + 8);
                
                (*sphb)[i][0][0] = b;
                
                memcpy(reinterpret_cast<char*>(sphb->data()) + 64 * i + 4, rest_30, 60);
            }
        }
        
        if (n)
        {
            auto& normals = obj->m_Desc.normals.host;
			
            normals->resize(n->count);
			
            memcpy(normals->data(), n->buffer.get(), n->buffer.size_bytes());
        }
        else
        {
            auto& normals = obj->m_Desc.normals.host;
			
            normals->resize(p->count, {});
        }
        
        {
            auto& albedos = obj->m_Desc.albedos.host;
			
            albedos->resize(p->count);
            
            memcpy(albedos->data(), obj->m_Desc.colors.host->data(), f_dc->buffer.size_bytes());
        }*/
        
        return true;
    }
    
}