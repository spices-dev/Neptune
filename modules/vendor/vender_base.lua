-- @file vender_base.lua.
-- @brief Defines vender_base Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Properties
local PROPERTIES = {
    includes           = true,
    library_dirs       = true,
    libraries          = true,
    dynamic_libraries  = true,
    project            = true,
}

-- @brief Create new vendor module.
--
-- @param[in] name Vendor Name.
--
-- @return Returns new module.
module.NewModule = function(name)

    local new_module      = {
        includes          = {},
        library_dirs      = {},
        libraries         = {},
        dynamic_libraries = {},
    }

    setmetatable(new_module, {
        __newindex = function(t, key, value)
            if not PROPERTIES[key] then
                error(string.format(
                    "[vendor:%s] Unknown Property: '%s', Allowed Properties:[includes, library_dirs, libraries, dynamic_libraries, project]",
                    name, key
                ), 2)
            end
            rawset(t, key, value)
        end
    })

    return new_module

end

return module