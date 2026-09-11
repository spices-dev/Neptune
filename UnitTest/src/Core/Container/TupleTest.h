/**
* @file TupleTest.h.
* @brief The TupleTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/Tuple.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {
    
    /**
    * @brief Testing IterTuple.
    */
    TEST(TupleTest, IterTuple) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        void* null = nullptr;

        auto t = std::make_tuple(1, 2.0f, "Hello", null, std::vector<int>{1, 2}, std::unordered_map<float, bool>{{1.0, true}});
        
        IterTuple(t, [&]<typename T>(const T& elem) {

            if constexpr ((std::is_same_v<T, int>))
            {
                EXPECT_EQ(elem, std::get<0>(t));

                return;
            }
            else if constexpr ((std::is_same_v<T, float>))
            {
                EXPECT_EQ(elem, std::get<1>(t));

                return;
            }
            else if constexpr ((std::is_same_v<T, const char*>))
            {
                EXPECT_EQ(elem, std::get<2>(t));

                return;
            }
            else if constexpr ((std::is_same_v<T, void*>))
            {
                EXPECT_EQ(elem, std::get<3>(t));

                return;
            }
            else if constexpr ((std::is_same_v<T, std::vector<int>>))
            {
                EXPECT_EQ(elem, std::get<4>(t));

                return;
            }
            else if constexpr ((std::is_same_v<T, std::unordered_map<float, bool>>))
            {
                EXPECT_EQ(elem, std::get<5>(t));

                return;
            }

            FAIL();
        });
    }
}