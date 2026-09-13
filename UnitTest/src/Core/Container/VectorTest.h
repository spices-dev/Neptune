/**
* @file VectorTest.h.
* @brief The VectorTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/Vector.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {

    /**
   * @brief Unit Test for Vector
   */
    class VectorTest : public testing::Test
    {
    protected:

        /**
        * @brief Interface on Initialize.
        */
        void SetUp() override {

            c0.PushBack("aaa");
            c0.PushBack("bbb");
            c0.PushBack("ccc");

            c1.PushBack(1);
            c1.PushBack(2);
            c1.PushBack(3);

            c2.PushBack(1.0f);
            c2.PushBack(2.0f);
            c2.PushBack(3.0f);
        }

        Vector<std::string> c0;    /* @brief Test Item. */
        Vector<int> c1;            /* @brief Test Item. */
        Vector<float> c2;          /* @brief Test Item. */
    };
    
    /**
    * @brief Testing Initialize.
    */
    TEST_F(VectorTest, Initialize) {

        NEPTUNE_TEST_PROFILE_FUNCTION
		
        EXPECT_EQ(c0.Size(), 3);
        EXPECT_EQ(c1.Size(), 3);
        EXPECT_EQ(c2.Size(), 3);
    }

    /**
    * @brief Testing FindElement.
    */
    TEST_F(VectorTest, FindElement) {

        NEPTUNE_TEST_PROFILE_FUNCTION
		
        auto v0 = c0.Get(0);
        EXPECT_EQ(v0, "aaa");
		
        auto v1 = c2.Get(10);
        EXPECT_EQ(v1, 0);
    }

    /**
    * @brief Testing if AddElement.
    */
    TEST_F(VectorTest, AddElement) {

        NEPTUNE_TEST_PROFILE_FUNCTION
		
        c0.PushBack("ddd");
        EXPECT_EQ(c0.Size(), 4);
		
        c1.PushBack(1);
        EXPECT_EQ(c1.Size(), 4);
        
        c2.PushBack(1.0f);
        EXPECT_EQ(c2.Size(), 4);
    }
    
    /**
    * @brief Testing Begin.
    */
    TEST_F(VectorTest, Begin) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        EXPECT_EQ(*c0.Begin(), "aaa");
        EXPECT_EQ(*c1.Begin(), 1);
        EXPECT_EQ(*c2.Begin(), 1.0f);
    }
}