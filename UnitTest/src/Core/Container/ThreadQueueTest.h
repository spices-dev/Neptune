/**
* @file ThreadQueueTest.h.
* @brief The ThreadQueueTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/ThreadQueue.hpp>
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
        void SetUp() override {}

        /**
        * @brief Interface on Shutdown.
        */
        void TearDown() override {}
    };

    /**
    * @brief Testing All.
    */
    TEST(ThreadQueueTest, All) {

        NEPTUNE_TEST_PROFILE_FUNCTION

    }
}