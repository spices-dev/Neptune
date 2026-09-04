/**
* @file Vertex.h.
* @brief The Vertex Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Header/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Neptune {

	/**
	* @brief Meshlet Class.
	* This class defines what Meshlet data.
	*/
	struct Meshlet : ShaderCore::Meshlet
	{
		/**
		* @brief Constructor Function.
		*/
		Meshlet() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Meshlet() = default;
	};

	/**
	* @brief Edge Class.
	* This class defines what Edge data.
	*/
	struct Edge : ShaderCore::HalfEdge
	{
		/**
		* @brief Constructor Function.
		*/
		Edge() = default;

		/**
		* @brief Constructor Function.
		* 
		* @param[in] f first.
		* @param[in] s second.
		*/
		Edge(uint32_t f, uint32_t s)
		{
			first  = f;
			second = s;
		}

		/**
		* @brief Destructor Function.
		*/
		virtual ~Edge() = default;

		/**
		* @brief Assignment Operation.
		* 
		* @param[in] other Another Edge.
		* 
		* @return Returns true if equal.
		*/
		bool operator==(const Edge& other) const {
			return (first == other.first && second == other.second) ||
				   (first == other.second && second == other.first);
		}

		/**
		* @brief Less Operation.
		* 
		* @param[in] other Another Edge.
		* 
		* @return Returns true if less than others.
		*/
		bool operator<(const Edge& other) const {
			return first < other.first;
		}
	};

	/**
	* @brief HalfEdge Class.
	* This class defines what HalfEdge data.
	*/
	struct HalfEdge : ShaderCore::HalfEdge
	{
		/**
		* @brief Constructor Function.
		*/
		HalfEdge() = default;

		/**
		* @brief Constructor Function.
		* 
		* @param[in] f first.
		* @param[in] s second.
		*/
		HalfEdge(uint32_t f, uint32_t s)
		{
			first  = f;
			second = s;
		}

		/**
		* @brief Destructor Function.
		*/
		virtual ~HalfEdge() = default;

		/**
		* @brief Assignment Operation.
		* 
		* @param[in] other Another Edge.
		* 
		* @return Returns true if equal.
		*/
		bool operator==(const HalfEdge& other) const {
			return first == other.first && second == other.second;
		}

		/**
		* @brief Less Operation.
		* 
		* @param[in] other Another HalfEdge.
		* 
		* @return Returns true if less than others.
		*/
		bool operator<(const HalfEdge& other) const {
			return first < other.first;
		}
	};

	/**
	* @brief EdgePoint Class.
	* This class defines what EdgePoint data.
	*/
	struct EdgePoint
	{
		/**
		* @brief Constructor Function.
		*/
		EdgePoint() = default;

		/**
		* @brief Constructor Function.
		* 
		* @param[in] prev Previous connected point.
		* @param[in] self This point.
		* @param[in] next Next connected point.
		*/
		EdgePoint(uint32_t prev, uint32_t self, uint32_t next)
			: prev(prev), self(self), next(next)
		{}

		/**
		* @brief Determine whether this edge point is valid.
		* 
		* @return Returns true if valid.
		*/
		bool valid()
		{
			return prev != (uint32_t)-1 && self != (uint32_t)-1 && next != (uint32_t)-1;
		}
		
		uint32_t prev = -1;
		uint32_t self = -1;
		uint32_t next = -1;
	};
}