/**
* @file BitSetTest.h.
* @brief The BitSetTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/BitSet.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

	namespace detail {
		
		enum class EBitSetTest : uint8_t
		{
			One,
			Two,
			Three,
			Four,
			
			Count
		};
	}
	
	/**
	* @brief Unit Test for BitSetTest
	*/
	class BitSetTest : public testing::Test
	{
	protected:

		/**
		* @brief Interface on Initialize.
		*/
		void SetUp() override {

			c0.Set(detail::EBitSetTest::One, true);
			c0.Set(detail::EBitSetTest::Two, true);
		}

		BitSet<detail::EBitSetTest> c0;    /* @brief Test Item. */
	};

	/**
	* @brief Testing Initialize.
	*/
	TEST_F(BitSetTest, Initialize) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		EXPECT_EQ(c0.Test(detail::EBitSetTest::One), true);
		EXPECT_EQ(c0.Test(detail::EBitSetTest::Two), true);
		EXPECT_EQ(c0.Test(detail::EBitSetTest::Three), false);
		EXPECT_EQ(c0.Test(detail::EBitSetTest::Four), false);
	}

	/**
	* @brief Testing Flip.
	*/
	TEST_F(BitSetTest, Flip) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		c0.Flip();
		
		EXPECT_EQ(c0.Test(detail::EBitSetTest::One), false);
		EXPECT_EQ(c0.Test(detail::EBitSetTest::Two), false);
		EXPECT_EQ(c0.Test(detail::EBitSetTest::Three), true);
		EXPECT_EQ(c0.Test(detail::EBitSetTest::Four), true);
		
		EXPECT_EQ(c0.Flip(detail::EBitSetTest::One), true);
		EXPECT_EQ(c0.Flip(static_cast<detail::EBitSetTest>(10)), false);
		
		EXPECT_EQ(c0.Test(detail::EBitSetTest::One), true);
	}

	/**
	* @brief Testing Any None.
	*/
	TEST_F(BitSetTest, Any_None) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		EXPECT_EQ(c0.Any(), true);
		
		EXPECT_EQ(c0.Set(detail::EBitSetTest::Count, false), true);
		EXPECT_EQ(c0.Set(static_cast<detail::EBitSetTest>(10), false), false);
		
		EXPECT_EQ(c0.None(), true);
	}

	/**
	* @brief Testing if Operator.
	*/
	TEST_F(BitSetTest, Operator) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		{
			BitSet<detail::EBitSetTest> c1;
		
			EXPECT_EQ(c0 == c1, false);
		
			EXPECT_EQ(c1.Set(detail::EBitSetTest::One, true), true);
			EXPECT_EQ(c1.Set(detail::EBitSetTest::Two, true), true);
		
			EXPECT_EQ(c0 == c1, true);
		}
		
		{
			BitSet<detail::EBitSetTest> c1;
		
			c1 = c0;
		
			EXPECT_EQ(c1.Test(detail::EBitSetTest::One), true);
			EXPECT_EQ(c1.Test(detail::EBitSetTest::Two), true);
			EXPECT_EQ(c0.Test(detail::EBitSetTest::Three), false);
			EXPECT_EQ(c0.Test(detail::EBitSetTest::Four), false);
		}
		
		{
			BitSet<detail::EBitSetTest> c1;
				
			EXPECT_EQ(c1.Set(detail::EBitSetTest::Three, true), true);
			EXPECT_EQ(c1.Set(detail::EBitSetTest::Four, true), true);
			
			c1 &= c0;
				
			EXPECT_EQ(c1.None(), true);
		}
		
		{
			BitSet<detail::EBitSetTest> c1;
						
			EXPECT_EQ(c1.Set(detail::EBitSetTest::Three, true), true);
			EXPECT_EQ(c1.Set(detail::EBitSetTest::Four, true), true);
					
			c1 |= c0;
						
			EXPECT_EQ(c1.Test(detail::EBitSetTest::Count), true);
		}
		
		{
			BitSet<detail::EBitSetTest> c1;
								
			EXPECT_EQ(c1.Set(detail::EBitSetTest::Four, true), true);
							
			c1 ^= c0;
								
			EXPECT_EQ(c1.Test(detail::EBitSetTest::One), true);
			EXPECT_EQ(c1.Test(detail::EBitSetTest::Two), true);
			EXPECT_EQ(c1.Test(detail::EBitSetTest::Three), false);
			EXPECT_EQ(c1.Test(detail::EBitSetTest::Four), true);
		}
	}

	/**
	* @brief Testing ThreadSafe.
	*/
	TEST_F(BitSetTest, ThreadSafe) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		c0.Reset();
		
		BitSet<detail::EBitSetTest> c1;
		
		constexpr uint32_t loop = 30000;
		
		auto t0 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				EXPECT_EQ(c1.Set(static_cast<detail::EBitSetTest>(i % static_cast<int>(detail::EBitSetTest::Count)), true), true);
			}
		});
		
		auto t1 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				EXPECT_EQ(c1.Set(static_cast<detail::EBitSetTest>(i % static_cast<int>(detail::EBitSetTest::Count)), false), true);
			}
		});
		
		auto t2 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c0 &= c1;
			}
		});
		
		auto t3 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c0 |= c1;
			}
		});
		
		auto t4 = std::thread([&]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int i = 0; i < loop; ++i)
			{
				c0 ^= c1;
			}
		});
		
		t0.join();
		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
}