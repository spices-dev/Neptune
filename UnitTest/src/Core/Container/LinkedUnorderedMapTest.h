/**
* @file LinkedUnorderedMapTest.h.
* @brief The LinkedUnorderedMapTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/LinkedUnorderedMap.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

	/**
	* @brief Unit Test for LinkedUnorderedMap
	*/
	class LinkedUnorderedMapTest : public testing::Test
	{
	protected:

		/**
		* @brief Interface on Initialize.
		*/
		void SetUp() override {

			c0.PushBack("aaa", "aaa");
			c0.PushBack("bbb", "bbb");
			c0.PushBack("ccc", "ccc");

			c1.PushBack(1, "1");
			c1.PushBack(2, "2");
			c1.PushBack(3, "3");

			c2.PushBack(1.0f, "1.0");
			c2.PushBack(2.0f, "2.0");
			c2.PushBack(3.0f, "3.0");
		}

		LinkedUnorderedMap<std::string, std::string> c0;    /* @brief Test Item. */
		LinkedUnorderedMap<int, std::string> c1;            /* @brief Test Item. */
		LinkedUnorderedMap<float, std::string> c2;          /* @brief Test Item. */
	};

	/**
	* @brief Testing Initialize.
	*/
	TEST_F(LinkedUnorderedMapTest, Initialize) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		EXPECT_EQ(c0.Size(), 3);
		EXPECT_EQ(c1.Size(), 3);
		EXPECT_EQ(c2.Size(), 3);
	}

	/**
	* @brief Testing RemoveElement.
	*/
	TEST_F(LinkedUnorderedMapTest, RemoveElement) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		c0.Clear();
		EXPECT_EQ(c0.Size(), 0);
		
		EXPECT_EQ(c1.Erase(1), true);
		EXPECT_EQ(c1.Size(), 2);
		
		EXPECT_EQ(c2.Erase(2.0f), true);
		EXPECT_EQ(c2.Erase(3.0f), true);
		EXPECT_EQ(c2.Size(), 1);
		
		EXPECT_EQ(c1.Erase(10), false);
		EXPECT_EQ(c1.Size(), 2);
	}

	/**
	* @brief Testing FindElement.
	*/
	TEST_F(LinkedUnorderedMapTest, FindElement) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		auto v = c0.At("aaa");
		EXPECT_EQ(v, "aaa");
		
		const bool isHasValue = c1.Contains(10);
		EXPECT_EQ(isHasValue, false);
		
		v = c2.At(10.0);
		EXPECT_EQ(v, "");
	}

	/**
	* @brief Testing if AddElement.
	*/
	TEST_F(LinkedUnorderedMapTest, AddElement) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		c0.PushBack("ddd", "ddd");
		EXPECT_EQ(c0.Size(), 4);
		
		c1.PushBack(1, "1");
		EXPECT_EQ(c1.Size(), 3);
		
		auto v = c2.At(1.0f);
		EXPECT_EQ(v, "1.0");
		c2.PushBack(1.0f, "10.0");
		v = c2.At(1.0f);
		EXPECT_EQ(v, "10.0");
	}

	/**
	* @brief Testing IteratorOrder.
	*/
	TEST_F(LinkedUnorderedMapTest, IteratorOrder) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		std::vector<std::string> iterOrder0;
		c0.ForEach([&](const std::string& k, const std::string& v) {
			
			iterOrder0.push_back(k);
			return false;
		});
		
		EXPECT_EQ(iterOrder0[0], "aaa");
		EXPECT_EQ(iterOrder0[1], "bbb");
		EXPECT_EQ(iterOrder0[2], "ccc");
		
		std::vector<int> iterOrder1;
		EXPECT_EQ(c1.Erase(2), true);
		c1.ForEach([&](const int& k, const std::string& v) {
			
			iterOrder1.push_back(k);
			return false;
		});
		EXPECT_EQ(iterOrder1[0], 1);
		EXPECT_EQ(iterOrder1[1], 3);
		
		std::vector<float> iterOrder2;
		c2.PushBack(0.5f, "0.5");
		c2.ForEach([&](const float& k, const std::string& v) {
			
			iterOrder2.push_back(k);
			return false;
		});
		
		EXPECT_EQ(iterOrder2[0], 1.0f);
		EXPECT_EQ(iterOrder2[1], 2.0f);
		EXPECT_EQ(iterOrder2[2], 3.0f);
		EXPECT_EQ(iterOrder2[3], 0.5f);
	}

	/**
	* @brief Testing NoLinearFind.
	*/
	TEST_F(LinkedUnorderedMapTest, NoLinearFind) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		EXPECT_EQ(c0.Prev("aaa"), "");
		EXPECT_EQ(c0.Prev("bbb"), "aaa");
		EXPECT_EQ(c0.Prev("ccc"), "bbb");
		
		EXPECT_EQ(c0.Next("aaa"), "bbb");
		EXPECT_EQ(c0.Next("bbb"), "ccc");
		EXPECT_EQ(c0.Next("ccc"),  "");
		
		LinkedUnorderedMap<std::string, std::string> c3;

		EXPECT_EQ(c0.Begin(), "aaa");
		EXPECT_EQ(c1.Begin(), "1");
		EXPECT_EQ(c2.Begin(), "1.0");
		EXPECT_EQ(c3.Begin(), "");
		
		EXPECT_EQ(c0.End(), "ccc");
		EXPECT_EQ(c1.End(), "3");
		EXPECT_EQ(c2.End(), "3.0");
		EXPECT_EQ(c3.End(), "");
		
		EXPECT_EQ(c0.EndK(), "ccc");
		EXPECT_EQ(c1.EndK(), 3);
		EXPECT_EQ(c2.EndK(), 3.0);
		EXPECT_EQ(c3.EndK(), "");
	}
	
	/**
	* @brief Testing ThreadSafe.
	*/
	TEST_F(LinkedUnorderedMapTest, ThreadSafe) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		c1.Clear();
		
		constexpr uint32_t loop = 30000;
		
		for (int i = 0; i < loop; ++i)
		{
			c1.PushBack(i,"");
		}
		
		auto t0 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c1.PushBack(i + loop,"");
			}
		});
		
		auto t1 = std::thread([&]() {
			while (!c1.Empty())
			{
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		});
		
		static std::atomic_uint64_t handle = 0;
		
		auto t2 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				while (!c1.Erase(handle)) {}

				++handle;
			}
		});
		
		auto t3 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				while (!c1.Erase(handle)) {}

				++handle;
			}
		});
		
		t0.join();
		t1.join();
		t2.join();
		t3.join();
		
		EXPECT_EQ(handle, loop * 2);
		EXPECT_EQ(c1.Empty(), true);
	}
}