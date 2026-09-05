/**
* @file Loader.cpp.
* @brief The Loader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Loader.h"
#include "Asset/SOP/Polygon.h"
#include "Asset/SOP/GS3D.h"

namespace Neptune::SOP {

	namespace {
		
		constexpr char kSOP[]     = "SOP";           // @brief SOP identify.
		constexpr char kPolygon[] = "Polygon";       // @brief Polygon identify.
		constexpr char kGS3D[]    = "GS3D";          // @brief GS3D identify.

		#pragma pack(push, 1)
		
		/**
		* @brief Asset Header Information.
		*/
		struct AssetHeader
		{
			char PrimaryType[100]   = {};       // @brief PrimaryType.
			char SecondaryType[100] = {};       // @brief SecondaryType.
		};
		
		#pragma pack(pop)
		
		static_assert(sizeof(AssetHeader) == 100 + 100);    // @brief Memory alignment check.
	}
	
	bool Loader::Load(const std::filesystem::path& file, Object* obj)
	{
		NEPTUNE_PROFILE_ZONE

		std::error_code ec;
		
		if (!std::filesystem::exists(file, ec)) {
			
			NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] do not exist.";
			
			return false;
		}
		
		std::ifstream stream(file, std::ios::binary);
		if (!stream.is_open())
		{
			NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] failed to open.";
			
			return false;
		}
		
		AssetHeader header;
		stream.read(reinterpret_cast<char*>(&header), sizeof(AssetHeader));
		
		if (!stream)
		{
			NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] data corruption.";
			
			return false;
		}
		
		if (std::strncmp(header.PrimaryType, kSOP, sizeof(header.PrimaryType)) != 0)
		{
			NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] is not a SOP asset. PrimaryType: " << header.PrimaryType;
			
			return false;
		}
		
		if (std::strncmp(header.SecondaryType, kPolygon, sizeof(header.SecondaryType)) == 0)
		{
			return Load(stream, static_cast<Polygon*>(obj));
		}
		
		if (std::strncmp(header.SecondaryType, kGS3D, sizeof(header.SecondaryType)) == 0)
		{
			return Load(stream, static_cast<GS3D*>(obj));
		}
		
		NEPTUNE_LOG_CORE(E) << "File: [ " << file << " ] has an unknown SecondaryType: " << header.SecondaryType;
		
		return false;
	}

	bool Loader::Load(MemoryBuffer& memory, Object* obj)
	{
		NEPTUNE_PROFILE_ZONE
		
		std::istream stream(&memory);
		
		AssetHeader header;
		stream.read(reinterpret_cast<char*>(&header), sizeof(AssetHeader));
		
		if (!stream)
		{
			NEPTUNE_LOG_CORE(E) << "Memory data corruption.";
			
			return false;
		}
		
		if (std::strncmp(header.PrimaryType, kSOP, sizeof(header.PrimaryType)) != 0)
		{
			NEPTUNE_LOG_CORE(E) << "Memory data is not a SOP asset. PrimaryType: " << header.PrimaryType;
			
			return false;
		}
		
		if (std::strncmp(header.SecondaryType, kPolygon, sizeof(header.SecondaryType)) == 0)
		{
			return Load(stream, static_cast<Polygon*>(obj));
		}
		
		if (std::strncmp(header.SecondaryType, kGS3D, sizeof(header.SecondaryType)) == 0)
		{
			return Load(stream, static_cast<GS3D*>(obj));
		}
		
		NEPTUNE_LOG_CORE(E) << "Memory data has an unknown SecondaryType: " << header.SecondaryType;
		
		return false;
	}
	
	bool Loader::Load(std::istream& stream, Polygon* obj)
	{
		NEPTUNE_PROFILE_ZONE
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& positions = obj->m_Desc.positions.host;
			
			positions->resize(count);
			
			stream.read(reinterpret_cast<char*>(positions->data()), sizeof(*positions));
		}

		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& normals = obj->m_Desc.normals.host;
			
			normals->resize(count);
			
			stream.read(reinterpret_cast<char*>(normals->data()), sizeof(*normals));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& colors = obj->m_Desc.colors.host;
				
			colors->resize(count);
			
			stream.read(reinterpret_cast<char*>(colors->data()), sizeof(*colors));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& texCoords = obj->m_Desc.texCoords.host;
			
			texCoords->resize(count);
			
			stream.read(reinterpret_cast<char*>(texCoords->data()), sizeof(*texCoords));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& vertices = obj->m_Desc.vertices.host;
			
			vertices->resize(count);
			
			stream.read(reinterpret_cast<char*>(vertices->data()), sizeof(*vertices));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& primitivePoints = obj->m_Desc.primitivePoints.host;
			
			primitivePoints->resize(count);
			
			stream.read(reinterpret_cast<char*>(primitivePoints->data()), sizeof(primitivePoints));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& primitiveVertices = obj->m_Desc.primitiveVertices.host;
			
			primitiveVertices->resize(count);
			
			stream.read(reinterpret_cast<char*>(primitiveVertices->data()), sizeof(primitiveVertices));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& primitiveLocations = obj->m_Desc.primitiveLocations.host;
			
			primitiveLocations->resize(count);
			
			stream.read(reinterpret_cast<char*>(primitiveLocations->data()), sizeof(primitiveLocations));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& meshlets = obj->m_Desc.meshlets.host;
			
			meshlets->resize(count);
			
			stream.read(reinterpret_cast<char*>(meshlets->data()), sizeof(meshlets));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			auto& lods = obj->m_Desc.lods.host;
			
			lods->resize(count);
			
			stream.read(reinterpret_cast<char*>(lods->data()), sizeof(lods));
		}
		
		obj->SetEObject(EObject::Polygon);
		
		obj->CreateRHIBuffer();
		
		return true;
	}

	bool Loader::Load(std::istream& stream, GS3D* obj)
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t count = 0;

		stream.read(reinterpret_cast<char*>(&count), sizeof(count));
		
		{
			auto& positions = obj->m_Desc.positions.host;
			
			positions->resize(count);
			
			stream.read(reinterpret_cast<char*>(positions->data()), sizeof(*positions));
		}
		
		{
			auto& normals = obj->m_Desc.normals.host;
			
			normals->resize(count);
			
			stream.read(reinterpret_cast<char*>(normals->data()), sizeof(normals));
		}
		
		{
			auto& colors = obj->m_Desc.colors.host;
			
			colors->resize(count);
			
			stream.read(reinterpret_cast<char*>(colors->data()), sizeof(*colors));
		}

		{
			auto& alphas = obj->m_Desc.alphas.host;
			
			alphas->resize(count);
			
			stream.read(reinterpret_cast<char*>(alphas->data()), sizeof(*alphas));
		}
		
		{
			auto& scales = obj->m_Desc.scales.host;
				
			scales->resize(count);
			
			stream.read(reinterpret_cast<char*>(scales->data()), sizeof(*scales));
		}
		
		{
			auto& orientations = obj->m_Desc.orientations.host;
			
			orientations->resize(count);
			
			stream.read(reinterpret_cast<char*>(orientations->data()), sizeof(*orientations));
		}
		
		{
			auto& albedos = obj->m_Desc.albedos.host;
			
			albedos->resize(count);
			
			stream.read(reinterpret_cast<char*>(albedos->data()), sizeof(*albedos));
		}
		
		obj->SetEObject(EObject::GS3D);
		
		obj->CreateRHIBuffer();
		
		return true;
	}
}