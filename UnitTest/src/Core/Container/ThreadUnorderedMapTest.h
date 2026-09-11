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
        void SetUp() override {}

        /**
        * @brief Interface on Shutdown.
        */
        void TearDown() override {}
    };

    /**
    * @brief Testing All.
    */
    TEST(ThreadUnorderedMapTest, All) {

        NEPTUNE_TEST_PROFILE_FUNCTION

    }
}