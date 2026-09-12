/**
* @file SpinLockTest.h.
* @brief The SpinLockTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/SpinLock.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

	/**
	* @brief Testing Definition.
	*/
	TEST(SpinLockTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		SpinLock mutex;
		
		mutex.lock();
		mutex.unlock();
		
		std::lock_guard lock(mutex);
	}
	
	/**
	* @brief Testing Counter.
	*/
	TEST(SpinLockTest, Counter) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		SpinLock mutex;
		
		constexpr uint64_t nThreads = 8;
		constexpr uint64_t loop     = 100000;

		long long counter = 0;
		std::vector<std::thread> threads;

		for (uint64_t i = 0; i < nThreads; ++i) 
		{
			threads.emplace_back([&] {
				for (uint64_t j = 0; j < loop; ++j) 
				{
					std::lock_guard lock(mutex);
					
					++counter;
				}
			});
		}

		for (auto& t : threads) t.join();

		EXPECT_EQ(counter, nThreads * loop);
	}
}