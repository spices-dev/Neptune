-- @file ffmpeg.lua.
-- @brief Defines ffmpeg Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("ffmpeg")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "windows" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/ffmpeg/win64/include",                              -- Include: ffmpeg
    }

    -- Library Directories
    module.library_dirs = {
        solution_root .. "/Neptune/vendor/ffmpeg/win64/lib",                                  -- Library: ffmpeg
    }

    -- Library Dependencies
    module.libraries = {
        "avcodec",                                                                            -- Library: avcodec
        "avdevice",                                                                           -- Library: avdevice
        "avfilter",                                                                           -- Library: avfilter
        "avformat",                                                                           -- Library: avformat
        "avutil",                                                                             -- Library: avutil
        "swresample",                                                                         -- Library: swresample
        "swscale",                                                                            -- Library: swscale
    }

    -- Dynamic Library Dependencies
    module.dynamic_libraries = {
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/avcodec-62.dll",                   -- Library: avcodec
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/avdevice-62.dll",                  -- Library: avdevice
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/avfilter-11.dll",                  -- Library: avfilter
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/avformat-62.dll",                  -- Library: avformat
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/avutil-60.dll",                    -- Library: avutil
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/swresample-6.dll",                 -- Library: swresample
        solution_root .. "/Neptune/vendor/ffmpeg/win64/bin/swscale-9.dll",                    -- Library: swscale
    }

end

return module