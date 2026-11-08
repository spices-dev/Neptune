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
		conformancemode "On"                  -- /permissive-

		-- MSVC Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_MSVC",                            -- Compiler: MSVC.
		}

		-- MSVC Specific Solution build options
		buildoptions 
		{
			"/utf-8",                                      -- Using utf-8 encode
		}

		-- MSVC Specific Solution disable warnings
		disablewarnings
        {
            "4324",                                        -- Structure alignment.
        }

		-- MSVC Specific Solution fatalwarnings
        fatalwarnings
        {
            "5038",                                        -- Initializer list order mismatch.
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
			"-fpch-preprocess",                            -- GCC pch flags
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
		}

	-- Configuration: Emcc Em++
	filter { "toolset:emcc" }
        
		-- Emcc Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_EMCC",                            -- Compiler: Emcc.
		}

		-- Emcc Specific Solution build options
		buildoptions 
		{
			"-pthread",                                    -- Enable pthread
			"-matomics",                                   -- Enable atomics
    		"-mbulk-memory",                               -- Enable bulk-memory
		}

	filter {}

end

-- @brief Enable Compiler Warning flags.
module.EnableMoreWarning = function()

    -- Configuration: MSVC
	filter { "toolset:msc*" }

		-- Enable warn.
		warnings "Extra"

		-- MSVC Specific Solution build options
		buildoptions 
		{                                       
			"/utf-8",                                      -- Using utf-8 encode
		}

	-- Configuration: Not MSVC
	filter { "toolset:not msc*" }

		-- Not MSVC Specific Solution build options
		buildoptions 
		{ 
			"-Wall",
            "-Wextra",
            "-Wpedantic",
            "-Wpointer-arith",
            "-Wunused-function",
            "-Wextra-semi",
		}

	-- Configuration: Clang
    filter { "toolset:clang" }

        buildoptions
        {
            "-Wimplicit-fallthrough",
            "-Wunreachable-code-return",
         -- "-Wconversion",
        }

	filter {}

end

return module