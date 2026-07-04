-- @file solution.lua.
-- @brief Defines all Solutions.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- @brief Use project and link it.
--
-- @param[in] project Inherited.
module.Uses = function(project)

    uses(project)

	links(project)

end

-- Projects
module.projects             = {
	["Neptune"]             = solution_root .. "/Neptune",            -- Project: Neptune
	["Editor"]              = solution_root .. "/Editor",             -- Project: Editor
	["Runtime"]             = solution_root .. "/Runtime",            -- Project: Runtime
    ["UnitTest"]            = solution_root .. "/UnitTest",           -- Project: UnitTest
}

-- @brief Load all Projects.
module.LoadProjects = function()

    for name, path in pairs(module.projects) do
        include(path)
    end

end

return module