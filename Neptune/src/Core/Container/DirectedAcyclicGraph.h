/**
* @file DirectedAcyclicGraph.h.
* @brief The DirectedAcyclicGraph Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <functional>

namespace Neptune::Container {

	/**
	* @brief DAG Class.
	*/
	template<typename T>
	class DirectedAcyclicGraph
	{
	public:
		
		/**
		* @brief DAG Node Class.
		*/
		class Node
		{
		public:

			/**
			* @brief Constructor Function.
			*/
			Node() = delete;

			/**
			* @brief Constructor Function.
			* 
			* @param[in] id Node id.
			* @param[in] dependencies Node dependencies.
			* @param[in] func Node function.
			*/
			Node(const T& id, const std::vector<T>& dependencies, const std::function<void()>& func)
				: m_Id(id)
				, m_Dependencies(dependencies)
				, m_Func(func)
			{}

			/**
			* @brief Destructor Function.
			*/
			virtual ~Node() = default;
		
		private:
		
			T m_Id;                                   // @brief Node id.
			std::vector<T> m_Dependencies;            // @brief Node dependencies.
			std::function<void()> m_Func;             // @brief Node function.
			
			friend class DirectedAcyclicGraph;
		};
		
	public:

		/**
		* @brief Constructor Function.
		*/
		DirectedAcyclicGraph() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~DirectedAcyclicGraph() = default;

		/**
		* @brief Add a node to this graph.
		* 
		* @param[in] node Node.
		*/
		void AddNode(Node* node)
		{
			m_Nodes[node->m_Id] = node;
		}

		/**
		* @brief Execute all node function by order.
		*/
		void Execute()
		{
			std::unordered_map<T, bool> visited;
		
			for (auto& node : m_Nodes)
			{
				if (!visited[node.first])
				{
					ExecuteInternal(node.second, visited);
				}
			}
		}

		/**
		* @brief Get Node size.
		* 
		* @return Returns Node size.
		*/
		size_t Size() const { return m_Nodes.size(); }

	private:

		/**
		* @brief Execute a node's function.
		* 
		* @param[in] node Node.
		* @param[in] visited graph execute states.
		*/
		void ExecuteInternal(Node* node, std::unordered_map<T, bool>& visited)
		{
			visited[node->m_Id] = true;
		
			for (auto& dep : node->m_Dependencies)
			{
				if (!visited[dep])
				{
					ExecuteInternal(m_Nodes[dep], visited);
				}
			}
		
			std::invoke(node->m_Func);
		}

	private:

		/**
		* @brief Graph Nodes.
		*/
		std::unordered_map<T, Node*> m_Nodes;
	};
	
}
