-- @file compiler.lua
-- @brief Defines all Solutions Toolset Env.
-- @author Spices.

-- Define module
local module = {}

-- @brief module Initialize.
module.Initialize = function()

    -- Configuration: MSVC
	filter { "toolset:msc*" }

		-- MSVC Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_MSVC",                            -- Compiler: MSVC.
		}

		-- MSVC Specific Solution build options
		buildoptions 
		{ 
			"/wd4838",                                     -- Disable Warning: 4838
			"/utf-8",                                      -- Using utf-8 encode
		}

	-- Configuration: GCC
    filter { "toolset:gcc" }
        
		-- GCC Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_GCC",                             -- Compiler: GCC.
		}

		-- GCC Specific Solution build options
		buildoptions 
		{ 
			"-Wno-narrowing"                               -- Disable Warning: 4838
		}          

	-- Configuration: Clang
	filter { "toolset:clang" }
		
		-- Clang Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_CLANG",                          -- Compiler: Clang.
		}

		-- Clang Specific Solution build options
		buildoptions 
		{ 
			"-Wno-narrowing",                             -- Disable Warning: 4838
		}

	-- Configuration: Emcc Em++
	filter { "toolset:emcc" }
        
		-- Emcc Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_EMCC",                           -- Compiler: Emcc.
		}

		-- Emcc Specific Solution build options
		buildoptions 
		{ 
			"-Wno-narrowing",                             -- Disable Warning: 4838
		}

end

return module