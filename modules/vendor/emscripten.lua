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

-- Define module
local module = {}

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