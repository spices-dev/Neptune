/**
* @file Attribute.h.
* @brief The Attribute Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"

namespace Neptune {

	/**
	* @brief MeshResource's item template.
	* 
	* @tparam T specific item value type.
	*/
	template<typename T>
	struct Attribute
	{
		/**
		* @brief Constructor Function.
		*/
		Attribute() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Attribute() = default;
		
		UP<std::vector<T>> attributes = CreateUP<std::vector<T>>();  // @brief Attribute Data Array.
		UP<RHI::Buffer> buffer = CreateUP<RHI::Buffer>();            // @brief Attribute RHI Buffer.
	};
}