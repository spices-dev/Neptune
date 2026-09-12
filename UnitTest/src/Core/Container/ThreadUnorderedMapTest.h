/**
* @file ThreadUnorderedMapTest.h.
* @brief The ThreadUnorderedMapTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/ThreadUnorderedMap.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

    /**
    * @brief Unit Test for ThreadUnorderedMap
    */
    class ThreadUnorderedMapTest : public testing::Test
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

        ThreadUnorderedMap<std::string, std::string> c0;    /* @brief Test Item. */
        ThreadUnorderedMap<int, std::string> c1;            /* @brief Test Item. */
        ThreadUnorderedMap<float, std::string> c2;          /* @brief Test Item. */
    };

    /**
	* @brief Testing Initialize.
	*/
	TEST_F(ThreadUnorderedMapTest, Initialize) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		EXPECT_EQ(c0.Size(), 3);
		EXPECT_EQ(c1.Size(), 3);
		EXPECT_EQ(c2.Size(), 3);
	}

	/**
	* @brief Testing RemoveElement.
	*/
	TEST_F(ThreadUnorderedMapTest, RemoveElement) {

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
	TEST_F(ThreadUnorderedMapTest, FindElement) {

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
	TEST_F(ThreadUnorderedMapTest, AddElement) {

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
	* @brief Testing ThreadSafe.
	*/
	TEST_F(ThreadUnorderedMapTest, ThreadSafe) {
        
		NEPTUNE_TEST_PROFILE_FUNCTION
        
		c1.Clear();
		
		constexpr uint32_t loop = 30000;
		
		for (int i = 0; i < loop; ++i)
		{
			c1.PushBack(i, "");
		}
		
		auto t0 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c1.PushBack(i + loop, "");
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