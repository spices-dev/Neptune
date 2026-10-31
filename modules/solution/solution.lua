-- @file solution.lua.
-- @brief Defines all Solutions.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Solution Output Directory
local output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- @brief Template of Define Project.
--
-- @param[in] config Project Config.
local TemplateDefineProject = function(config)

    project(config.name)

        -- Kind Config.
        kind(config.kind)

        -- Use Runtime Library: MDD.
        staticruntime "Off"

        -- Language Config.
        if config.language == "C++" then
            language "C++"                       -- Use C++.
            cppdialect "C++20"                   -- Use C++20.
        elseif config.language == "C" then
            language "C"                         -- Use C.
        end

        -- Building Output Folder.
        targetdir("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")

        -- Building Object Folder.
        objdir("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

        -- Enable Multi Processor Compile
        multiprocessorcompile "On"

        -- Reset filter
        filter {}

        -- Execute Project specific configs
        config.callback()

        -- Reset filter
        filter {}

end

-- @brief Use project and link it.
--
-- @param[in] project Inherited.
module.Uses = function(project)

    uses(project)

	links(project)

end

-- @brief Define C Static Library.
--
-- @param[in] name Project Name.
-- @param[in] callback Project specific configs
module.DefineCStaticLibrary = function(name, callback)

    TemplateDefineProject({
        name     = name,
        kind     = "StaticLib",
        language = "C",
        callback = callback
    })

end

-- @brief Define Cpp Static Library.
--
-- @param[in] name Project Name.
-- @param[in] callback Project specific configs
module.DefineCppStaticLibrary = function(name, callback)

    TemplateDefineProject({
        name     = name,
        kind     = "StaticLib",
        language = "C++",
        callback = callback
    })

end

-- @brief Define Cpp Shared Library.
--
-- @param[in] name Project Name.
-- @param[in] callback Project specific configs
module.DefineCppSharedLibrary = function(name, callback)

    TemplateDefineProject({
        name     = name,
        kind     = "SharedLib",
        language = "C++",
        callback = callback
    })

end

-- @brief Define Cpp Executable.
--
-- @param[in] name Project Name.
-- @param[in] callback Project specific configs
module.DefineCppExecutable = function(name, callback)

    TemplateDefineProject({
        name     = name,
        kind     = "ConsoleApp",
        language = "C++",
        callback = function()

            callback()

            -- Platform: Android
            filter "system:android"

                -- Android: shared library
                kind "SharedLib"

            filter {}

            -- Private Config
            usage "PRIVATE"

                -- Reset filter
                filter {}

                links(platform.GetExecutableLinks())

                linkoptions(platform.GetExecutableLinkOptions())

                -- Reset filter
                filter {}

        end
    })

end

-- Projects
module.projects = function()

    local list = {}

    table.insert(list, solution_root .. "/Neptune")                   -- Project: Neptune
    table.insert(list, solution_root .. "/Editor")                    -- Project: Editor
    table.insert(list, solution_root .. "/Runtime")                   -- Project: Runtime
    table.insert(list, solution_root .. "/UnitTest")                  -- Project: UnitTest

    return list

end

-- @brief Load all Projects.
module.LoadProjects = function()

    for _, path in ipairs(module.projects()) do
        include(path)
    end

end

-- @brief Solution Output Directory.
module.OutputDirectory = output_dir

return module