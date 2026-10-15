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

	bool Loader::Load(Container::MemoryBuffer& memory, Object* obj)
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
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "positions buffer is empty.";
				
				return false;
			}
			
			auto& positions = obj->m_Desc.positions.host;
			
			positions->resize(count);
			
			stream.read(reinterpret_cast<char*>(positions->data()), count * sizeof(Decay<decltype(*positions)>::value_type));
		}

		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "normals buffer is empty.";
				
				return false;
			}
			
			auto& normals = obj->m_Desc.normals.host;
			
			normals->resize(count);
			
			stream.read(reinterpret_cast<char*>(normals->data()), count * sizeof(Decay<decltype(*normals)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "colors buffer is empty.";
				
				return false;
			}
			
			auto& colors = obj->m_Desc.colors.host;
				
			colors->resize(count);
			
			stream.read(reinterpret_cast<char*>(colors->data()), count * sizeof(Decay<decltype(*colors)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "texCoords buffer is empty.";
				
				return false;
			}
			
			auto& texCoords = obj->m_Desc.texCoords.host;
			
			texCoords->resize(count);
			
			stream.read(reinterpret_cast<char*>(texCoords->data()), count * sizeof(Decay<decltype(*texCoords)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "vertices buffer is empty.";
				
				return false;
			}
			
			auto& vertices = obj->m_Desc.vertices.host;
			
			vertices->resize(count);
			
			stream.read(reinterpret_cast<char*>(vertices->data()), count * sizeof(Decay<decltype(*vertices)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "primitivePoints buffer is empty.";
				
				return false;
			}
			
			auto& primitivePoints = obj->m_Desc.primitivePoints.host;
			
			primitivePoints->resize(count);
			
			stream.read(reinterpret_cast<char*>(primitivePoints->data()), count * sizeof(Decay<decltype(*primitivePoints)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "primitiveVertices buffer is empty.";
				
				return false;
			}
			
			auto& primitiveVertices = obj->m_Desc.primitiveVertices.host;
			
			primitiveVertices->resize(count);
			
			stream.read(reinterpret_cast<char*>(primitiveVertices->data()), count * sizeof(Decay<decltype(*primitiveVertices)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "primitiveLocations buffer is empty.";
				
				return false;
			}
			
			auto& primitiveLocations = obj->m_Desc.primitiveLocations.host;
			
			primitiveLocations->resize(count);
			
			stream.read(reinterpret_cast<char*>(primitiveLocations->data()), count * sizeof(Decay<decltype(*primitiveLocations)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "meshlets buffer is empty.";
				
				return false;
			}
			
			auto& meshlets = obj->m_Desc.meshlets.host;
			
			meshlets->resize(count);
			
			stream.read(reinterpret_cast<char*>(meshlets->data()), count * sizeof(Decay<decltype(*meshlets)>::value_type));
		}
		
		{
			uint32_t count = 0;

			stream.read(reinterpret_cast<char*>(&count), sizeof(count));
			
			if (count == 0)
			{
				NEPTUNE_LOG_CORE(E) << "lods buffer is empty.";
				
				return false;
			}
			
			auto& lods = obj->m_Desc.lods.host;
			
			lods->resize(count);
			
			stream.read(reinterpret_cast<char*>(lods->data()), count * sizeof(Decay<decltype(*lods)>::value_type));
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
		
		if (count == 0)
		{
			NEPTUNE_LOG_CORE(E) << "GS3D buffer is empty.";
				
			return false;
		}
		
		/*{
			auto& positions = obj->m_Desc.positions.host;
			
			positions->resize(count);
			
			stream.read(reinterpret_cast<char*>(positions->data()), count * sizeof(Decay<decltype(*positions)>::value_type));
		}
		
		{
			auto& normals = obj->m_Desc.normals.host;
			
			normals->resize(count);
			
			stream.read(reinterpret_cast<char*>(normals->data()), count * sizeof(Decay<decltype(*normals)>::value_type));
		}
		
		{
			auto& colors = obj->m_Desc.colors.host;
			
			colors->resize(count);
			
			stream.read(reinterpret_cast<char*>(colors->data()), count * sizeof(Decay<decltype(*colors)>::value_type));
		}

		{
			auto& alphas = obj->m_Desc.alphas.host;
			
			alphas->resize(count);
			
			stream.read(reinterpret_cast<char*>(alphas->data()), count * sizeof(Decay<decltype(*alphas)>::value_type));
		}
		
		{
			auto& scales = obj->m_Desc.scales.host;
				
			scales->resize(count);
			
			stream.read(reinterpret_cast<char*>(scales->data()), count * sizeof(Decay<decltype(*scales)>::value_type));
		}
		
		{
			auto& orientations = obj->m_Desc.orientations.host;
			
			orientations->resize(count);
			
			stream.read(reinterpret_cast<char*>(orientations->data()), count * sizeof(Decay<decltype(*orientations)>::value_type));
		}
		
		{
			auto& albedos = obj->m_Desc.albedos.host;
			
			albedos->resize(count);
			
			stream.read(reinterpret_cast<char*>(albedos->data()), count * sizeof(Decay<decltype(*albedos)>::value_type));
		}
		
		obj->SetEObject(EObject::GS3D);
		
		obj->CreateRHIBuffer();*/
		
		return true;
	}
}