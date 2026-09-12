/**
* @file TreeTest.h.
* @brief The TreeTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <gmock/gmock.h>
#include <Core/Container/Tree.h>
#include <array>

namespace Neptune::Container::Test {

	/**
	* @brief Unit Test for Tree
	*/
	class TreeTest : public testing::Test
	{
	protected:

		/**
		* @brief Interface on Initialize.
		*/
		void SetUp() override {}

		/**
		* @brief Interface on Shutdown.
		*/
		void TearDown() override {}

	protected:
		
		Tree<int> m_Tree;
	};
	
	/**
	* @brief Testing Constructor.
	*/
	TEST_F(TreeTest, Constructor) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		{
			EXPECT_EQ(m_Tree.GetData(), 0);
		}
		
		{
			const Tree<float> tree;
			
			EXPECT_FLOAT_EQ(tree.GetData(), 0.0f);
		}

		{
			const Tree<void*> tree;
			
			EXPECT_EQ(tree.GetData(), nullptr);
		}

		{
			struct TestStruct
			{
				int a = 1;
				float b = 2.0f;
			};

			const Tree<TestStruct> tree;

			EXPECT_EQ(tree.GetData().a, 1);
			EXPECT_FLOAT_EQ(tree.GetData().b, 2.0f);
		}
	}

	/**
	* @brief Testing AddChild.
	*/
	TEST_F(TreeTest, AddChild) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		auto child = &m_Tree;
		
		for (int i = 0; i < 1000; i++)
		{
			child = child->AddChild(i);

			EXPECT_EQ(child->GetData(), i);
		}
	}

	/**
	* @brief Testing View.
	*/
	TEST_F(TreeTest, View) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		m_Tree.View([](const auto& data) {

			EXPECT_EQ(data, 0);
		});

		m_Tree.SetData(1);

		m_Tree.View([](const auto& data) {
			
			EXPECT_EQ(data, 1);
		});
	}

	/**
	* @brief Testing ViewDSF ViewWSF.
	*/
	TEST_F(TreeTest, ViewDSF_ViewWSF) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		const auto c0 = &m_Tree;
		
		// max depth = 3
		for (int i = 0; i < 10; i++)
		{
			const auto c1 = c0->AddChild(i);

			for (int j = 0; j < 10; j++)
			{
				const auto c2 = c1->AddChild(j);

				for (int k = 0; k < 10; k++)
				{
					const auto c3 = c2->AddChild(k);
				}
			}
		}

		{
			uint32_t count = 0;

			m_Tree.ViewDSF([&](const auto& data, uint32_t depth) {

				++count;
				return false;
			});

			EXPECT_EQ(count, 1 + 10 + 100 + 1000);
		}

		{
			uint32_t count = 0;

			m_Tree.ViewWSF([&](const auto& data, uint32_t depth) {

				++count;
				return false;
			});

			EXPECT_EQ(count, 1 + 10 + 100 + 1000);
		}

		{
			uint32_t count = 0;

			m_Tree.ViewDSF([&](const auto& data, uint32_t depth) {

				if (depth == 3)
				{
					return true;
				}

				++count;
				return false;
			});

			EXPECT_EQ(count, 1 + 1 + 1);
		}

		{
			uint32_t count = 0;

			m_Tree.ViewWSF([&](const auto& data, uint32_t depth) {

				if (depth == 3)
				{
					return true;
				}

				++count;
				return false;
			});

			EXPECT_EQ(count, 1 + 10 + 100);
		}
	}
	
	/**
	* @brief Testing ThreadSafe.
	*/
	TEST_F(TreeTest, ThreadSafe) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		const auto c0 = &m_Tree;
		
		auto t0 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			for (int i = 0; i < 10; ++i)
			{
				const auto c1 = c0->AddChild(i);

				for (int j = 0; j < 10; ++j)
				{
					const auto c2 = c1->AddChild(j);

					for (int k = 0; k < 10; ++k)
					{
						const auto c3 = c2->AddChild(k);
					}
				}
			}
		});
		
		auto t1 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			for (int i = 0; i < 10; ++i)
			{
				const auto c1 = c0->AddChild(i);

				for (int j = 0; j < 10; ++j)
				{
					const auto c2 = c1->AddChild(j);

					for (int k = 0; k < 10; ++k)
					{
						const auto c3 = c2->AddChild(k);
					}
				}
			}
		});
		
		t0.join();
		t1.join();
		
		std::array<uint32_t, 4> count { 0 };
		
		m_Tree.ViewWSF([&](const auto& data, uint32_t depth) {
			count[depth] += data;
			
			return false;
		});
		
		EXPECT_EQ(count[0], 0);
		
		{
			uint32_t data = 0;
			
			for (int i = 0; i < 10; ++i) { data += 2 * i; }
			
			EXPECT_EQ(count[1], data);
		}
		
		{
			uint32_t data = 0;
			
			for (int i = 0; i < 20; ++i) { for (int j = 0; j < 10; ++j) { data += j; } }
			
			EXPECT_EQ(count[2], data);
		}
		
		{
			uint32_t data = 0;
			
			for (int i = 0; i < 20; ++i) { for (int j = 0; j < 10; ++j) { for (int k = 0; k < 10; ++k) { data += k; } } }
			
			EXPECT_EQ(count[3], data);
		}
	}
	
}