-- @file AdaptiveCpp.lua.
-- @brief Defines AdaptiveCpp Third Party.
-- @author Spices.

-- @brief Get AdaptiveCpp Path.
--
-- @return Returns AdaptiveCpp Path.
local GetAdaptiveCppPath = function()

    local paths = {
        windows = "C:/AdaptiveCpp",
        linux   = "",
        macosx  = ""
    }

    return paths[os.target()] or ""

end

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("AdaptiveCpp")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "windows" then

    -- Includes
    module.includes = {
        GetAdaptiveCppPath() .. "/include",                                                         -- Include: AdaptiveCpp
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

end

return module