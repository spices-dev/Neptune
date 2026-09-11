/**
* @file TimerTest.h.
* @brief The TimerTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Timer/Timer.h>
#include <gmock/gmock.h>

namespace Neptune {

    /**
    * @brief Testing All.
    */
    TEST(TimerTest, All) {

        NEPTUNE_TEST_PROFILE_FUNCTION

        Timer timer;
        
        static constexpr float esp = 0.1f;
        
        for (int i = 0; i < 100; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            
            timer.Flush();
            
            EXPECT_LE(timer.DurationTime() - i * 10.0f, esp);
            
            EXPECT_LE(timer.SegmentTime() - 10.0f, esp);
        }
        
    }

}