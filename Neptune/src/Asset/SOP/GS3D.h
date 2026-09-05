/**
* @file GS3D.h.
* @brief The GS3D Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "DescBase.h"
#include "Object.h"

namespace Neptune::Tool {
	
	class Ply;
}

namespace Neptune::SOP {
	
	/**
	* @brief GS3D Description.
	*/
	struct GS3DDesc : DescBase<ShaderCore::GS3DDesc>
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
		
		using Positions           = Attribute<glm::vec3>;               
		using Colors              = Attribute<glm::vec3>;               
		using Alphas              = Attribute<float>;
		using Scales              = Attribute<glm::vec3>;               
		using Orientations        = Attribute<glm::vec4>;   

		using SPH_R               = Attribute<glm::mat4>;      
		using SPH_G               = Attribute<glm::mat4>;      
		using SPH_B               = Attribute<glm::mat4>;      

		using Normals             = Attribute<glm::vec3>;  
		using Albedos             = Attribute<glm::vec3>;
		
		Positions                   positions;                           // @brief Position.
		Colors                      colors;                              // @brief Color.
		Alphas                      alphas;                              // @brief Alphas.
		Scales                      scales;                              // @brief Scales.
		Orientations                orientations;                        // @brief Orientations.
		
		SPH_R                       sphrs;                               // @brief SPH_R.
		SPH_G                       sphgs;                               // @brief SPH_G.
		SPH_B                       sphbs;                               // @brief SPH_B.
		
		Normals                     normals;                             // @brief Normal.
		Albedos                     albedos;                             // @brief Albedos.
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
		uint32_t GetPointCount() const { return m_Desc.positions.host->size(); }
		
		/**
		* @brief Get Desc Device Address.
		* 
		* @return Returns Desc Device Address.
		*/
		const uint64_t& GetDescDeviceAddress() const { return m_Desc.descAddress; }
		
	private:

		GS3DDesc m_Desc{};   // @brief GS3D Description.
		
		friend class Loader;
		friend class Tool::Ply;
	};
}