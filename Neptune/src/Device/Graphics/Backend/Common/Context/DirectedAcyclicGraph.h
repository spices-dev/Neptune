/**
* @file DirectedAcyclicGraph.h.
* @brief The DirectedAcyclicGraph Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"
#include "Core/Container/BitSet.h"

#include <bitset>

namespace Neptune::Graphic::Common {
	
	/**
	* @brief DirectedAcyclicGraph for static enum dependency check.
	* 
	* @tparam E Enum.
	*/
	template<IsNotEmptyEnum E>
	struct DirectedAcyclicGraph
	{
		static constexpr uint8_t N = static_cast<uint8_t>(E::Count);  // @brief Enum Count.
		
		using Deps = std::bitset<N>;  // @brief std::bitset Dependencies.

		/**
		* @brief DAG Node.
		*/
		struct Entry
		{
			E                        node;      // @brief node
			std::initializer_list<E> deps;      // @brief dependencies
		};
		
		/**
		* @brief Constructor Function.
		*/
		constexpr DirectedAcyclicGraph() = default;
		
		/**
		* @brief Constructor Function.
		* 
		* @tparam M uint8_t.
		* @param[in] entries Nodes.
		*/
		template<uint8_t M>
		constexpr DirectedAcyclicGraph(const Entry(&entries)[M])
		{
			for (uint8_t i = 0; i < M; ++i)
			{
				const auto from = static_cast<uint8_t>(entries[i].node);

				for (E dep : entries[i].deps)
				{
					const auto to = static_cast<std::size_t>(dep);

					m_Nodes[from].set(to);
				}
			}
		}
		
		/**
		* @brief Execute.
		* 
		* @return Returns true if passed.
		*/
		constexpr bool Execute() const
		{
			for (uint8_t i = 0; i < N; ++i)
			{
				for (uint8_t j = i; j < N; ++j)
				{
					if (m_Nodes[i].test(j)) return false;
				}
			}
			
			return true;
		}
		
		/**
		* @brief Get Dependencies.
		* 
		* @tparam I uint8_t.
		* 
		* @return Returns Dependencies.
		*/
		template<uint8_t I>
		constexpr Deps Dependencies() const
		{
			return m_Nodes[I];
		}
		
		std::array<Deps, N> m_Nodes{};   // @brief Nodes.
	};
	
	/**
	* @brief Infrastructure DAG.
	*/
	template<IsNotEmptyEnum E>
	inline constexpr DirectedAcyclicGraph<E> s_InfrastructureDAG {};
}