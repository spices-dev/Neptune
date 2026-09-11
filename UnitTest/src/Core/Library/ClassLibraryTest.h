/**
* @file ClassLibraryTest.h.
* @brief The ClassLibraryTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Library/ClassLibrary.h>
#include <gmock/gmock.h>

namespace Neptune::Library::Test {
    
    class TestClass0 {};
    class TestClass1 {};

    /**
    * @brief Testing GetClassString.
    */
    TEST(LibraryTest, GetClassString) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        EXPECT_EQ(GetClassString(typeid(TestClass0)), "TestClass0");
        EXPECT_EQ(GetClassString(typeid(TestClass1)), "TestClass1");
    }
}