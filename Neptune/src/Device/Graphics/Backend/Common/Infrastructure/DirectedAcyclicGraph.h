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
	
	template<IsNotEmptyEnum E>
	struct DirectedAcyclicGraph
	{
		static constexpr uint8_t N = static_cast<uint8_t>(E::Count);
		
		using Deps = std::bitset<N>;
		
		struct Entry
		{
			E    node;
			std::initializer_list<E> deps;
		};
		
		constexpr DirectedAcyclicGraph() = default;
		
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
		
		std::array<Deps, N> m_Nodes{};
	};
}