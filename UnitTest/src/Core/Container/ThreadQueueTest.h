/**
* @file ThreadQueueTest.h.
* @brief The ThreadQueueTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/ThreadQueue.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

    /**
    * @brief Unit Test for ThreadQueue
    */
    class ThreadQueueTest : public testing::Test
    {
    protected:

        /**
        * @brief Interface on Initialize.
        */
        void SetUp() override {

            c0.Push("aaa");
            c0.Push("bbb");
            c0.Push("ccc");

            c1.Push(1);
            c1.Push(2);
            c1.Push(3);

            c2.Push(1.0f);
            c2.Push(2.0f);
            c2.Push(3.0f);
        }

        ThreadQueue<std::string> c0;    /* @brief Test Item. */
        ThreadQueue<int> c1;            /* @brief Test Item. */
        ThreadQueue<float> c2;          /* @brief Test Item. */
    };

    /**
	* @brief Testing Initialize.
	*/
	TEST_F(ThreadQueueTest, Initialize) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		EXPECT_EQ(c0.Size(), 3);
		EXPECT_EQ(c1.Size(), 3);
		EXPECT_EQ(c2.Size(), 3);
	}

	/**
	* @brief Testing RemoveElement.
	*/
	TEST_F(ThreadQueueTest, RemoveElement) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		c0.Clear();
		EXPECT_EQ(c0.Size(), 0);
		
		EXPECT_EQ(c1.Pop(), 1);
		EXPECT_EQ(c1.Size(), 2);
		
		EXPECT_EQ(c2.Pop(), 1.0f);
		EXPECT_EQ(c2.Pop(), 2.0f);
		EXPECT_EQ(c2.Size(), 1);
		
		EXPECT_EQ(c1.Pop(), 2);
		EXPECT_EQ(c1.Size(), 1);
	}

	/**
	* @brief Testing if AddElement.
	*/
	TEST_F(ThreadQueueTest, AddElement) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		c0.Push("ddd");
		EXPECT_EQ(c0.Size(), 4);
		
		c1.Push(1);
		EXPECT_EQ(c1.Size(), 4);
		
		c2.Push(1.0f);
		EXPECT_EQ(c1.Size(), 4);
	}
    
    /**
    * @brief Testing ThreadSafe.
    */
    TEST_F(ThreadQueueTest, ThreadSafe) {
        
        NEPTUNE_TEST_PROFILE_FUNCTION

		c1.Clear();
		
		constexpr uint32_t loop = 3000;
		
		for (int i = 0; i < loop; ++i)
		{
			c1.Push(i);
		}
		
		auto t0 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c1.Push(i + loop);
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
				c1.Pop();
				++handle;
			}
		});
		
		auto t3 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c1.Pop();
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