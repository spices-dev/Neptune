/**
* @file Mesh.h.
* @brief The Mesh Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "MeshPack.h"
#include "Core/Container/LinkedUnorderedMap.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Neptune {

	enum class CullMode
	{
		None = 0,
		Front,
		Back,

		Count
	};

	/**
	* @brief Mesh Class.
	*/
	class Mesh
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Mesh() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Mesh() = default;

		/**
		* @brief Add pack to mesh.
		* 
		* @param[in] meshPack Which pack we want to add to.
		* 
		* @return Returns this reference.
		*/
		Mesh& AddPack(const SP<MeshPack>& meshPack);

	private:
		
		SP<Container::LinkedUnorderedMap<uint32_t, SP<MeshPack>>> m_Pack = CreateUP<Container::LinkedUnorderedMap<uint32_t, SP<MeshPack>>>();  // @brief The packs that used for create mesh.
	};
}