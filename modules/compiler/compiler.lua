-- @file compiler.lua
-- @brief Defines all Solutions Toolset Env.
-- @author Spices.

-- Define module
local module = {}

-- @brief module Initialize.
module.Initialize = function()

    -- Configuration: MSVC
	filter { "toolset:msc*" }

											  -- tracy use __FILE__ in constexpr, but MSVC do not support it by default.
											  -- There are two way to handle with that:
											  -- 1.Use a complex format of __LINE__:
											  --   #define _DBJ_CONCATENATE_(a, b) a ## b
											  --   #define _DBJ_CONCATENATE(a, b)  _DBJ_CONCATENATE_(a, b)
                                              --   #define CONSTEXPR_LINE long(_DBJ_CONCATENATE(__LINE__,U)) 
		editAndContinue "Off"				  -- 2.Use DebugInfoFormat: Zi (Program Database).

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
			"-pthread",                                   -- Enable pthread
			"-matomics",                                  -- Enable atomics
    		"-mbulk-memory",                              -- Enable bulk-memory
		}

	filter {}

end

return module