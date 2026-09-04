-- @file ImGuizmo.lua.
-- @brief Defines ImGuizmo Third Party.
-- @author Spices.

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("ImGuizmo")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/ImGuizmo",                                                -- Include: ImGuizmo
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module