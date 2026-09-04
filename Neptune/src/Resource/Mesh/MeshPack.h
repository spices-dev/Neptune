/**
* @file MeshPack.h.
* @brief The MeshPack Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Vertex.h"
#include "Resource/ResourcePool/ResourcePool.h"
#include "Attribute.h"
#include "Header/Core.h"

namespace Neptune {
	
	/**
	* @brief Lod Data.
	*/
	struct Lod
	{
		uint32_t primVertexOffset;     /* @brief Lod PrimVertexOffset (also PrimPointOffset).    */
		uint32_t nPrimitives;          /* @brief Lod PrimVertices Count (also PrimPoints Count). */
		uint32_t meshletOffset;        /* @brief Lod MeshletOffset.                              */
		uint32_t nMeshlets;            /* @brief Lod Meshlets Count.                             */
	};

	/**
	* @brief Mesh Resources Data.
	*/
	struct MeshResource
	{
		/**
		* @brief Constructor Function.
		*/
		MeshResource() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~MeshResource() = default;
		
		using Positions           = Attribute<glm::vec3>;               
		using Normals             = Attribute<glm::vec3>;               
		using Colors              = Attribute<glm::vec3>;               
		using TexCoords           = Attribute<glm::vec2>;               
		using Vertices            = Attribute<glm::uvec4>;              

		using PrimitivePoints     = Attribute<glm::uvec3>;              
		using PrimitiveVertices   = Attribute<glm::uvec3>;              
		using PrimitiveLocations  = Attribute<glm::uvec3>;              
		using Meshlets            = Attribute<Meshlet>;                 
		using Lods                = Attribute<Lod>;                     
		
		Positions                   positions;                           // @brief Position.(also as Point)
		Normals                     normals;                             // @brief Normal
		Colors                      colors;                              // @brief Color
		TexCoords                   texCoords;                           // @brief TexCoord
		Vertices                    vertices;                            // @brief Vertex.
		PrimitivePoints             primitivePoints;                     // @brief PrimPoints
		PrimitiveVertices           primitiveVertices;                   // @brief PrimVertices
		PrimitiveLocations          primitiveLocations;                  // @brief PrimLocation
		Meshlets                    meshlets;                            // @brief PrimMeshlet
		Lods                        lods;                                // @brief Lod
	};

	/**
	* @brief MeshPack Class.
	* This class need to be inherited while use.
	*/
	class MeshPack : public NonCopyable
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] name MeshPack Name.
		* @param[in] instanced Is this mesh pack instanced.
		*/
		MeshPack(const std::string& name, bool instanced);

		/**
		* @brief Destructor Function.
		*/
		virtual ~MeshPack() = default;

		/**
		* @brief This interface is used for build specific mesh pack data.
		* 
		* @param[in] isCreateBuffer Whether it needs to create buffer.
		* 
		* @return Returns true if copy resource from Pool.
		*/
		virtual bool OnCreatePack(bool isCreateBuffer = true);
		
		/**
		* @brief Get mesh pack UUID.
		*/
		UUID GetUUID() const { return m_UUID; }

		/**
		* @brief Get Resource.
		* @return Returns the Resource.
		*/
		const MeshResource& GetResource() const { return m_MeshResource; }

	protected:

		/**
		* @brief Create Vertices buffer anf Indices buffer.
		*/
		void CreateBuffer();

	protected:
		
		std::string m_MeshPackName;   // @brief MeshPack Name.
		bool m_Instanced;             // @brief If this mesh pack needs instanced.
		MeshResource m_MeshResource;  // @brief Mesh Resources.
		ShaderCore::MeshDesc m_Desc;  // @brief Mesh Description.
		UUID m_UUID;                  // @brief UUID for mesh pack.

		/**
		* @brief Allow MeshLoader access all data.
		*/
		friend class MeshLoader;
		friend class MeshProcessor;
	};
}
