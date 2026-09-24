/**
* @file EmptyTest.h.
* @brief The EmptyTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Container/Empty.h>
#include <gmock/gmock.h>

namespace Neptune::Container::Test {
    
    namespace detail {
        
        class EmptyTest0 : public Empty {};
        class EmptyTest1 : public Empty { int a = 0; };
        class EmptyTest2  { [[no_unique_address]] Empty e; int a = 0; };
    }
    
    /**
    * @brief Testing Definition.
    */
    TEST(EmptyTest, Definition) {

        NEPTUNE_TEST_PROFILE_FUNCTION
        
        EXPECT_EQ(sizeof(Empty), 1);
        
        {
            Empty c;
        
            EXPECT_EQ(sizeof(c), 1);
        }
        
        {
            detail::EmptyTest0 c;
        
            EXPECT_EQ(sizeof(c), 1);
        }
        
        {
            detail::EmptyTest0 c;
        
            EXPECT_EQ(sizeof(c), 1);
        }
        
        {
            detail::EmptyTest1 c;
        
            EXPECT_EQ(sizeof(c), 4);
        }
        
        {
            detail::EmptyTest2 c;
        
            EXPECT_EQ(sizeof(c), 4);
        }
    }
}
