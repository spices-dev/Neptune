-- @file emscripten.lua.
-- @brief Defines emscripten Third Party.
-- @author Spices.

-- @brief Get Emsdk Path.
--
-- @return Returns Emsdk Path.
local GetEmsdkPath = function()

    local paths = {
        windows = "C:/emsdk",
        linux   = "",
        macosx  = ""
    }

    return paths[os.target()] or ""

end

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("emscripten")

if os.target() == "emscripten" then

    -- Includes
    module.includes = {
        GetEmsdkPath() .. "/upstream/emscripten/cache/sysroot/include/"                      -- Include: emscripten
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

end

return module