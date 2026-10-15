/**
* @file GS3D.h.
* @brief The GS3D Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "DescBase.h"
#include "Object.h"
#include "Header/GS3DTileRenderCore.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::Tool {
	
	class Sog;
}

namespace Neptune::SOP {
	
	/**
	* @brief GS3D Description.
	*/
	struct GS3DDesc : DescBase<ShaderCore::GS3DTileRenderCore::GS3DDesc>
	{
		/**
		* @brief Constructor Function.
		*/
		GS3DDesc() = default;

		/**
		* @brief Destructor Function.
		*/
		~GS3DDesc() override = default;
		
		/**
		* @brief Upload Host data to Device.
		*/
		void UploadToDevice() override;
		
		using MeansRanges          = Attribute<glm::vec3>;    
		using ScaleCodes           = Attribute<float>;    
		using Sh0Codes             = Attribute<float>;    

		MeansRanges                        meansRanges;                       // @brief MeansRanges.
		ScaleCodes                         scaleCodes;                        // @brief ScaleCodes.
		Sh0Codes                           sh0Codes;                          // @brief Sh0Codes.
		
		SP<RenderTarget>                   means_0;                           // @brief Position.
		SP<RenderTarget>                   means_1;                           // @brief Position.
		SP<RenderTarget>                   scales;                            // @brief Scale.
		SP<RenderTarget>                   quats;                             // @brief Orientation.
		SP<RenderTarget>                   sh0;                               // @brief SH.
	};
	
	/**
	* @brief GS3D Class.
	*/
	class GS3D : public Object
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] file FilePath.
		*/
		explicit GS3D(const std::filesystem::path& file) : Object(file) {}

		/**
		* @brief Destructor Function.
		*/
		~GS3D() override = default;

		/**
		* @brief Load Data from Disk.
		* 
		* @return Returns true if succeeded.
		*/
		bool LoadFromDisk() override;
		
		/**
		* @brief Create RHI Buffer.
		*/
		void CreateRHIBuffer() override;
		
		/**
		* @brief Get Point Count.
		* 
		* @return Returns Point Count.
		*/
		uint32_t GetPointCount() const { return m_Count; }
		
		/**
		* @brief Get GS3DDesc.
		* 
		* @return Returns GS3DDesc.
		*/
		const GS3DDesc& GetDesc() const { return m_Desc; }
		
		/**
		* @brief Get Desc Device Address.
		* 
		* @return Returns Desc Device Address.
		*/
		const uint64_t& GetDescDeviceAddress() const { return m_Desc.descAddress; }
		
	private:

		GS3DDesc m_Desc{};       // @brief GS3D Description.
		uint32_t m_Count = 0;    // @brief GS3D Count.
		
		friend class Loader;
		friend class Tool::Sog;
	};
}