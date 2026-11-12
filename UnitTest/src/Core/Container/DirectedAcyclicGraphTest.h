/**
* @file DirectedAcyclicGraphTest.h.
* @brief The DirectedAcyclicGraphTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/DirectedAcyclicGraph.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

	/**
	* @brief Unit Test for DirectedAcyclicGraphTest
	*/
	class DirectedAcyclicGraphTest : public testing::Test
	{
	protected:

		/**
		* @brief Testing class initialize function.
		*/
		void SetUp() override {}

		/**
		* @brief Testing class TearDown function.
		*/
		void TearDown() override {}

		std::vector<DirectedAcyclicGraph<std::string>::Node> m_Nodes;

		DirectedAcyclicGraph<std::string> m_DAG;
	};

	/**
	* @brief Testing AddNode.
	*/
	TEST_F(DirectedAcyclicGraphTest, AddNode) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		m_Nodes.push_back({ "A", {"C"}, [](){}});
		m_Nodes.push_back({ "B", {"A"}, [](){}});
		m_Nodes.push_back({ "C", {}, [](){}});

		for (int i = 0; i < m_Nodes.size(); i++)
		{
			m_DAG.AddNode(&m_Nodes[i]);
		}
		
		EXPECT_EQ(m_Nodes.size(), 3);
		EXPECT_EQ(m_DAG.Size(), 3);
	}

	/**
	* @brief Testing Execute.
	*/
	TEST_F(DirectedAcyclicGraphTest, Execute) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		std::stringstream ss;
		
		auto functor = [&](const std::string& name) {
			
			ss << name;
		};

		m_Nodes.push_back({ "A", {"C"}, std::bind(functor, "A")});
		m_Nodes.push_back({ "B", {"A"}, std::bind(functor, "B")});
		m_Nodes.push_back({ "C", {}, std::bind(functor, "C")});

		for (int i = 0; i < m_Nodes.size(); i++)
		{
			m_DAG.AddNode(&m_Nodes[i]);
		}

		m_DAG.Execute();
		
		EXPECT_EQ(ss.str(), std::string("CAB"));
		EXPECT_EQ(m_Nodes.size(), 3);
		EXPECT_EQ(m_DAG.Size(), 3);
	}
}