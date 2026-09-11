/**
* @file SpinLockTest.h.
* @brief The SpinLockTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/SpinLock.hpp>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

	/**
	* @brief Unit Test for SpinLock
	*/
	class SpinLockTest : public testing::Test
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
	};

	/**
	* @brief Testing All.
	*/
	TEST(SpinLockTest, All) {

		NEPTUNE_TEST_PROFILE_FUNCTION

	}
}