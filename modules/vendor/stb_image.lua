-- @file stb_image.lua.
-- @brief Defines stb_image Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("stb_image")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/stb_image",                                               -- Include: stb_image
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module