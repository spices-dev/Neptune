/**
* @file StringLibraryTest.h.
* @brief The StringLibraryTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Library/StringLibrary.h>
#include <gmock/gmock.h>

namespace Neptune::Library::Test {

    /**
    * @brief Testing SplitString.
    */
    TEST(StringLibraryTest, SplitString) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        std::string s = "Hello,my friend,it is a good day.";
        auto result = SplitString(s, ',');

        EXPECT_EQ(result.size(), 3);

        EXPECT_STREQ(result[0].c_str(), "Hello");
        EXPECT_STREQ(result[1].c_str(), "my friend");
        EXPECT_STREQ(result[2].c_str(), "it is a good day.");
    }

    /**
    * @brief Testing SplitKeepString.
    */
    TEST(StringLibraryTest, SplitKeepString) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        std::string s = "Hello,my friend,it is a good day.";
        auto result = SplitKeepString(s, ',');

        EXPECT_EQ(result.size(), 3);

        EXPECT_STREQ(result[0].c_str(), "Hello,");
        EXPECT_STREQ(result[1].c_str(), "my friend,");
        EXPECT_STREQ(result[2].c_str(), "it is a good day.");
    }
}