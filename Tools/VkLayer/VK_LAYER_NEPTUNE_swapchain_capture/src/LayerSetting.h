/**
* @file LayerSetting.h.
* @brief The LayerSetting Class Definitions.
* @author Spices.
*/
#pragma once

namespace Neptune {
    
    /**
    * @brief LayerSetting Data.
    */
    struct Settings
    {
        std::string save_path;             // @brief Save Path.
        uint32_t capture_every_n_frames;   // @brief Capture Every N Frames.
        uint32_t max_captures;             // @brief Max Captures.
        
        uint64_t frameId = 0;              // @brief Frame id.
        uint32_t captured_frames = 0;      // @brief Captured frames count.
    };
}