/**
* @file Sog.cpp.
* @brief The Sog Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Sog.h"
#include "Asset/SOP/GS3D.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Buffer/Buffer.h"

#include <miniz.h>
#include <nlohmann/json.hpp>
#include <src/webp/decode.h>

namespace Neptune::Tool {
    
    bool Sog::Load(const std::filesystem::path& file, SOP::GS3D* obj)
    {
        NEPTUNE_PROFILE_ZONE
        
        std::error_code ec;
		
        if (!std::filesystem::exists(file, ec)) {
			
            NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] do not exist.";
			
            return false;
        }
        
        auto files = UnZip(file);
        
        auto meta = nlohmann::json::parse(files["meta.json"]);
        
        auto means_mins      = meta["means"]["mins"].get<std::vector<float>>();
        auto means_maxs      = meta["means"]["maxs"].get<std::vector<float>>();
        auto scale_codebook  = meta["scales"]["codebook"].get<std::vector<float>>();
        auto sh0_codebook    = meta["sh0"]["codebook"].get<std::vector<float>>();
        
        auto means_l    = DecodeWebp(files[meta["means"]["files"][0].get<std::string>()]);
        auto means_u    = DecodeWebp(files[meta["means"]["files"][1].get<std::string>()]);
        auto scales_img = DecodeWebp(files[meta["scales"]["files"][0].get<std::string>()]);
        auto quats_img  = DecodeWebp(files[meta["quats"]["files"][0].get<std::string>()]);
        auto sh0_img    = DecodeWebp(files[meta["sh0"]["files"][0].get<std::string>()]);
        
        means_l->SetName("means_0");
        means_l->SetName("means_1");
        means_l->SetName("scales");
        means_l->SetName("quats");
        means_l->SetName("sh0");

        obj->m_Count        = meta["count"];
        
        auto& meansRanges = *obj->m_Desc.meansRanges.host;
        meansRanges.resize(2);
        meansRanges[0] = { means_mins[0], means_mins[1], means_mins[2] };
        meansRanges[1] = { means_maxs[0], means_maxs[1], means_maxs[2] };
            
        auto& scaleCodes = *obj->m_Desc.scaleCodes.host;
        scaleCodes.resize(scale_codebook.size());
        std::memcpy(scaleCodes.data(), scale_codebook.data(), scale_codebook.size());
        
        auto& sh0Codes = *obj->m_Desc.sh0Codes.host;
        sh0Codes.resize(sh0_codebook.size());
        std::memcpy(sh0Codes.data(), sh0_codebook.data(), sh0_codebook.size());
        
        obj->m_Desc.means_0 = means_l;
        obj->m_Desc.means_1 = means_u;
        obj->m_Desc.scales  = scales_img;
        obj->m_Desc.quats   = quats_img;
        obj->m_Desc.sh0     = sh0_img;
        
        obj->SetEObject(EObject::GS3D);
		
        obj->CreateRHIBuffer();
        
        return true;
    }
    
    std::unordered_map<std::string, std::vector<uint8_t>> Sog::UnZip(const std::filesystem::path& file)
    {
        NEPTUNE_PROFILE_ZONE
        
        std::ifstream stream(file, std::ios::binary | std::ios::ate);
        
        std::streamsize size = stream.tellg();
        stream.seekg(0, std::ios::beg);
        
        std::vector<uint8_t> sog(size);
        stream.read(reinterpret_cast<char*>(sog.data()), size);
        
        mz_zip_archive zip = {};
        mz_zip_reader_init_mem(&zip, sog.data(), sog.size(), 0);
        
        std::unordered_map<std::string, std::vector<uint8_t>> result;
        
        mz_uint count = mz_zip_reader_get_num_files(&zip);
        
        for (mz_uint i = 0; i < count; ++i) 
        {
            mz_zip_archive_file_stat stat;
            if (!mz_zip_reader_file_stat(&zip, i, &stat)) continue;

            std::string name = stat.m_filename;

            if (mz_zip_reader_is_file_a_directory(&zip, i)) continue;

            std::vector<uint8_t> buf(stat.m_uncomp_size);
            
            if (mz_zip_reader_extract_to_mem(&zip, i, buf.data(), buf.size(), 0))
            {
                result.emplace(std::move(name), std::move(buf));
            }
        }

        mz_zip_reader_end(&zip);
        
        return result; 
    }

    SP<RenderTarget> Sog::DecodeWebp(const std::vector<uint8_t>& buf)
    {
        NEPTUNE_PROFILE_ZONE
        
        int width, height;
        
        WebPGetInfo(buf.data(), buf.size(), &width, &height);
        
        std::vector<uint8_t> data(width * height * 4);
        
        WebPDecodeRGBAInto(buf.data(), buf.size(), data.data(),  width * height * 4, width * 4);

        BufferCreateInfo              bufferInfo{};
        bufferInfo.size             = data.size();
        bufferInfo.usage            = { Graphic::EBufferUsage::TransferSrc, Graphic::EBufferUsage::TransferDst };
        
        SP<Buffer> buffer = CreateSP<Buffer>(bufferInfo);
        
        buffer->GetRHIResource()->WriteToBuffer(data.data(), data.size());
        
        buffer->GetRHIResource()->Flush(data.size());
        
        RenderTargetCreateInfo           imageInfo{};
        imageInfo.width                = width;
        imageInfo.height               = height;
        imageInfo.domain               = TextureDomain::Texture2D;
        imageInfo.format               = TextureFormat::RGBA8_UINT;
        imageInfo.usage                = { Graphic::EImageUsage::Sampler, Graphic::EImageUsage::TransferDst };
        
        SP<RenderTarget> renderTarget = CreateSP<RenderTarget>(imageInfo);
        
        renderTarget->CopyFromBuffer(buffer);
        
        return renderTarget;
    }
}