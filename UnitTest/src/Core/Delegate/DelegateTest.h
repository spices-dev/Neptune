/**
* @file DelegateTest.h.
* @brief The DelegateTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Delegate/DelegateBasic.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <gmock/gmock.h>

namespace Neptune::Test {
	
	namespace detail
	{
		class DelegateFuncTest
		{
		public:
			
			void        Test()              {}
			void        Test(float f)       {}
			void        Test0(int a, int b) {}
			static void Test1()             {}
		};
		
		template<typename ...Args>
		void DelegateTestT(Args&& ...args) {}
		
		DELEGATE(Test0)
		DELEGATE(Test1, float)
		DELEGATE(Test2, int, int)
		DELEGATE(Test3, glm::vec2, glm::vec2, glm::vec2)
		DELEGATE(Test4, glm::vec3, glm::vec3, glm::vec3, glm::vec3)
		DELEGATE(Test5, glm::vec4, glm::vec4, glm::vec4, glm::vec4, glm::vec4)
		DELEGATE(Test6, bool, bool, bool, bool, bool, bool)
		DELEGATE(Test7, bool, bool, bool, bool, bool, bool, bool)
		DELEGATE(Test8, bool, bool, bool, bool, bool, bool, bool, bool)
		DELEGATE(Test9, bool, bool, bool, bool, bool, bool, bool, bool, bool)
	}
	
	/**
	* @brief Unit Test for Delegate
	*/
	class DelegateTest : public testing::Test
	{
	protected:

		detail::DelegateTest0 test0;
		detail::DelegateTest1 test1;
		detail::DelegateTest2 test2;
		detail::DelegateTest3 test3;
		detail::DelegateTest4 test4;
		detail::DelegateTest5 test5;
		detail::DelegateTest6 test6;
		detail::DelegateTest7 test7;
		detail::DelegateTest8 test8;
		detail::DelegateTest9 test9;
	};

	/**
	* @brief Testing Bind UnBind.
	*/
	TEST_F(DelegateTest, Bind_UnBind) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		detail::DelegateFuncTest funcTestClass;

		{
			EXPECT_EQ(0, test0.Bind(std::bind((void(detail::DelegateFuncTest::*)())&detail::DelegateFuncTest::Test, &funcTestClass)));                                // @brief Override Class Function.
			EXPECT_EQ(0, test1.Bind(std::bind((void(detail::DelegateFuncTest::*)(float))&detail::DelegateFuncTest::Test, &funcTestClass, std::placeholders::_1)));    // @brief Override Class Function.
			EXPECT_EQ(0, test2.Bind(std::bind(&detail::DelegateFuncTest::Test0, &funcTestClass, std::placeholders::_1, std::placeholders::_2)));                      // @brief Class Function.
			EXPECT_EQ(1, test0.Bind(std::bind(&detail::DelegateFuncTest::Test1)));                                                                                    // @brief Static Class Function.
			EXPECT_EQ(2, test0.Bind(std::bind(&detail::DelegateFuncTest::Test1)));                                                                                    // @brief Repeat Static Class Function.

			EXPECT_EQ(3, test0.Bind([&]() { return funcTestClass.Test(); }));                                                                                   // @brief Lambda Override Class Function.
			EXPECT_EQ(1, test1.Bind([&](float f) { return funcTestClass.Test(f); }));																           // @brief Lambda Override Class Function.
			EXPECT_EQ(1, test2.Bind([&](int a, int b) { return funcTestClass.Test0(a, b); }));														           // @brief Lambda Class Function.
			EXPECT_EQ(4, test0.Bind([&]() { return detail::DelegateFuncTest::Test1(); }));																       // @brief Lambda Static Class Function.
			EXPECT_EQ(5, test0.Bind([&]() { return detail::DelegateTestT(); }));										                                           // @brief Lambda Template Function.

			EXPECT_EQ(2, test1.Bind([](bool val) { return val; }));                                                                                             // @brief Lambda Function.
		
			EXPECT_EQ(test0.Size(), 6);
			EXPECT_EQ(test1.Size(), 3);
			EXPECT_EQ(test2.Size(), 2);
		
			EXPECT_EQ(test0.Empty(), false);
			EXPECT_EQ(test1.Empty(), false);
			EXPECT_EQ(test2.Empty(), false);
		}
		
		{
			test0.UnBind(0);
			test0.UnBind(1);
			test0.UnBind(2);
			test0.UnBind(3);
			test0.UnBind(4);
			test0.UnBind(5);

			EXPECT_EQ(test0.Size(), 0);
			EXPECT_EQ(test0.Empty(), true);
		}
		
		{
			EXPECT_EQ(6, test0.Bind(std::bind((void(detail::DelegateFuncTest::*)())&detail::DelegateFuncTest::Test, &funcTestClass)));
			
			EXPECT_EQ(test0.Size(), 1);
			EXPECT_EQ(test0.Empty(), false);
		}
	}

	/**
	* @brief Testing Broadcast.
	*/
	TEST_F(DelegateTest, Broadcast) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		uint32_t iter = 0;
		
		test1.Bind([&](const auto& a) {
			iter += a;
		});
		
		test1.Bind([&](const auto& a) {
			iter += a + 10;
		});
		
		test1.Bind([&](const auto& a) {
			iter += a + 100;
		});
		
		test1.Broadcast(1);

		EXPECT_EQ(iter, 1 + 11 + 101);
		
		test1.UnBind(2);
		
		test1.Broadcast(2);
		
		EXPECT_EQ(iter, 1 + 11 + 101 + 2 + 12);
		
		EXPECT_EQ(test1.Size(), 2);
		EXPECT_EQ(test1.Empty(), false);
	}

	/**
	* @brief Testing Copy.
	*/
	TEST_F(DelegateTest, Copy) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		detail::DelegateFuncTest funcTestClass;
		
		{
			test2.Bind(std::bind(&detail::DelegateFuncTest::Test0, &funcTestClass, std::placeholders::_1, std::placeholders::_2));

			EXPECT_EQ(test2.Size(), 1);
			EXPECT_EQ(test2.Empty(), false);
		}
		
		{
			detail::DelegateTest2 test2c = test2;

			EXPECT_EQ(test2c.Size(), 1);
			EXPECT_EQ(test2c.Empty(), false);

			test2c.UnBind(0);

			EXPECT_EQ(test2.Size(), 0);
			EXPECT_EQ(test2.Empty(), true);
		}
	}
	
	/**
	* @brief Testing ThreadSafe.
	*/
	TEST_F(DelegateTest, ThreadSafe) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		constexpr uint32_t loop = 30000;
		
		std::atomic_uint32_t iter = 0;
		
		for (int i = 0; i < loop; ++i)
		{
			EXPECT_EQ(test1.Bind([&](const auto& a) { iter += a; }), i);
		}
		
		auto t0 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				EXPECT_EQ(test1.Bind([&](const auto& a) { iter += a; }), i + loop);
			}
		});
		
		std::atomic_uint64_t handle = 0;

		auto t1 = std::thread([&]() {
			while (!test1.Empty())
			{
				test1.Broadcast(1);
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		});
		
		auto t2 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				auto h = handle++;

				while (!test1.UnBind(h)) {}
			}
		});
		
		auto t3 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				auto h = handle++;

				while (!test1.UnBind(h)) {}
			}
		});
		
		t0.join();
		t1.join();
		t2.join();
		t3.join();
		
		EXPECT_EQ(handle, loop * 2);
		EXPECT_EQ(test1.Empty(), true);
	}
}
