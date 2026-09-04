/**
* @file Polygon.h.
* @brief The Polygon Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Header/Core.h"
#include "Object.h"
#include "Attribute.h"

namespace Neptune::SOP {
	
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
	* @brief Polygon Description.
	*/
	struct PolygonDesc : ShaderCore::PolygonDesc
	{
		/**
		* @brief Constructor Function.
		*/
		PolygonDesc() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~PolygonDesc() = default;
		
		using Positions           = Attribute<glm::vec3>;               
		using Normals             = Attribute<glm::vec3>;               
		using Colors              = Attribute<glm::vec3>;               
		using TexCoords           = Attribute<glm::vec2>;               
		using Vertices            = Attribute<glm::uvec4>;              

		using PrimitivePoints     = Attribute<glm::uvec3>;              
		using PrimitiveVertices   = Attribute<glm::uvec3>;              
		using PrimitiveLocations  = Attribute<glm::uvec3>;              
		using Meshlets            = Attribute<ShaderCore::Meshlet>;                 
		using Lods                = Attribute<Lod>;                     
		
		Positions                   positions;                           // @brief Position.
		Normals                     normals;                             // @brief Normal.
		Colors                      colors;                              // @brief Color.
		TexCoords                   texCoords;                           // @brief TexCoord.
		Vertices                    vertices;                            // @brief Vertex.
		PrimitivePoints             primitivePoints;                     // @brief PrimPoints.
		PrimitiveVertices           primitiveVertices;                   // @brief PrimVertices.
		PrimitiveLocations          primitiveLocations;                  // @brief PrimLocation.
		Meshlets                    meshlets;                            // @brief PrimMeshlet.
		Lods                        lods;                                // @brief Lod.
	};
	
	/**
	* @brief Polygon Class.
	*/
	class Polygon : public Object
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] file FilePath.
		*/
		explicit Polygon(const std::filesystem::path& file): Object(file) {}

		/**
		* @brief Destructor Function.
		*/
		~Polygon() override = default;

	private:

		PolygonDesc m_Desc;    // @brief Description.
		
		friend class Loader;
	};
}