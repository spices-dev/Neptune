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
    * @brief Testing PushBack.
    */
    TEST(Vector, PushBack) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        {
            Vector<int> v;
            
            for (int i = 0; i < 100000; i++)
            {
                v.PushBack(i);

                EXPECT_EQ(v.Size(), i + 1);
                EXPECT_EQ(v.Empty(), false);
            }
        }

        {
            Vector<void*> v;

            void* p = nullptr;

            for (int i = 0; i < 100000; i++)
            {
                v.PushBack(p);

                EXPECT_EQ(v.Size(), i + 1);
                EXPECT_EQ(v.Empty(), false);
            }
        }

        {
            Vector<Vector<void*>> v;

            void* p = nullptr;

            for (int i = 0; i < 100000; i++)
            {
                Vector<void*> t;

                t.PushBack(p);
                v.PushBack(t);

                EXPECT_EQ(v.Size(), i + 1);
                EXPECT_EQ(v.Empty(), false);
            }
        }
    }

    /**
    * @brief Testing Get.
    */
    TEST(Vector, Get) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        Vector<int> v;

        EXPECT_EQ(v.Get(200000), 0);
        
        for (int i = 0; i < 100000; i++)
        {
            v.PushBack(i);

            EXPECT_EQ(v.Size(), i + 1);
            EXPECT_EQ(v.Empty(), false);
        }

        for (int i = 0; i < 100000; i++)
        {
            EXPECT_EQ(v.Get(i), i);
        }
        
        EXPECT_EQ(v.Get(200000), 0);
    }
    
    /**
    * @brief Testing Begin End.
    */
    TEST(Vector, Begin_End) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        Vector<int> v;

        for (int i = 100; i < 100000; i++)
        {
            v.PushBack(i);

            EXPECT_EQ(v.Size(), i + 1 - 100);
            EXPECT_EQ(v.Empty(), false);
        }

        EXPECT_EQ(*v.Begin(), 100);
    }
}