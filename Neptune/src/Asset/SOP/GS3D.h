/**
* @file GS3D.h.
* @brief The GS3D Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Header/Core.h"
#include "Object.h"
#include "Attribute.h"

namespace Neptune::Tool {
	
	class Ply;
}

namespace Neptune::SOP {
	
	/**
	* @brief GS3D Description.
	*/
	struct GS3DDesc : ShaderCore::GS3DDesc
	{
		/**
		* @brief Constructor Function.
		*/
		GS3DDesc() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~GS3DDesc() = default;
		
		/**
		* @brief Upload Host data to Device.
		*/
		void UploadToDevice() const;
		
		using Positions           = Attribute<glm::vec3>;               
		using Normals             = Attribute<glm::vec3>;               
		using Colors              = Attribute<glm::vec3>;               
		using Alphas              = Attribute<glm::vec3>;               
		using Scales              = Attribute<glm::vec3>;               
		using Orientations        = Attribute<glm::vec4>;               
		using Albedos             = Attribute<glm::vec3>;               
		
		Positions                   positions;                           // @brief Position.
		Normals                     normals;                             // @brief Normal.
		Colors                      colors;                              // @brief Color.
		Alphas                      alphas;                              // @brief Alphas.
		Scales                      scales;                              // @brief Scales.
		Orientations                orientations;                        // @brief Orientations.
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
		void CreateRHIBuffer() const override;
		
	private:

		GS3DDesc m_Desc{};   // @brief GS3D Description.
		
		friend class Loader;
		friend class Tool::Ply;
	};
}