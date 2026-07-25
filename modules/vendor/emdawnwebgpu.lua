-- @file emdawnwebgpu.lua.
-- @brief Defines emdawnwebgpu Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "emscripten" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/emdawnwebgpu/webgpu/include",                             -- Include: emdawnwebgpu
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

end

return module