/**
* @file BitSetTest.h.
* @brief The BitSetTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/BitSet.hpp>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

	namespace detail {
		
		enum class EBitSetTest : uint8_t
		{
			Count
		};
	}
	
	/**
	* @brief Unit Test for BitSet
	*/
	class BitSetTest : public testing::Test
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

		BitSet<detail::EBitSetTest> m_BitSet;
	};

	/**
	* @brief Testing All.
	*/
	TEST(BitSetTest, All) {

		NEPTUNE_TEST_PROFILE_FUNCTION

	}
}