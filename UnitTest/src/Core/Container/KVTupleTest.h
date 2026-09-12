/**
* @file KVTupleTest.h.
* @brief The KVTupleTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/KVTuple.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {
    
    namespace detail {
        
        enum class EKVTupleEnum : uint8_t
        {
            Zero,
            One,
            Two,
            
            Count,
        };
    }
    
    /**
    * @brief Testing Definition.
    */
    TEST(KVTupleTest, Definition) {

        NEPTUNE_TEST_PROFILE_FUNCTION
        
        {
            KVTuple<int, detail::EKVTupleEnum::Zero> c;
        
            EXPECT_EQ(c.E, detail::EKVTupleEnum::Zero);
            
            constexpr bool v = std::is_same_v<decltype(c)::T, int>;
        
            EXPECT_EQ(v, true);
        }
        
        {
            KVTuple<float, detail::EKVTupleEnum::One> c;
        
            EXPECT_EQ(c.E, detail::EKVTupleEnum::One);
            
            constexpr bool v = std::is_same_v<decltype(c)::T, float>;
        
            EXPECT_EQ(v, true);
        }
        
        {
            KVTuple<std::string, detail::EKVTupleEnum::Two> c;
                
            EXPECT_EQ(c.E, detail::EKVTupleEnum::Two);
            
            constexpr bool v = std::is_same_v<decltype(c)::T, float>;
        
            EXPECT_EQ(v, false);
        }
        
        
    }
}
