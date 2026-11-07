/**
* @file ImageWriter.h.
* @brief The ImageWriter Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <filesystem>

namespace Neptune {
    
    /**
    * @brief Save image to Png.
    * 
    * @param path File path.
    * @param data Image data.
    * @param w Image width.
    * @param h Image height.
    * @param pixelBytes Image pixel bytes.
    * 
    * @return Returns true if succeeded.
    */
    bool SavePng(const std::filesystem::path& path, const void* data, uint32_t w, uint32_t h, uint32_t pixelBytes);
    
}