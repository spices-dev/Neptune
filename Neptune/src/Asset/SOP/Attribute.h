/**
* @file Attribute.h.
* @brief The Attribute Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"

namespace Neptune::SOP {

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
		
		UP<std::vector<T>> host = CreateUP<std::vector<T>>();  // @brief Attribute Host Data.
		UP<RHI::Buffer> device  = CreateUP<RHI::Buffer>();     // @brief Attribute Device Data.
	};
}