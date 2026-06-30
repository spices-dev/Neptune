-- @file vendor.lua.
-- @brief Defines all Solutions Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Sub Vendor Scripts
local sub_vendor  = {
    windows       = current_dir .. "windows.lua",
    linux         = current_dir .. "linux.lua",
    macosx        = current_dir .. "macos.lua",
    emscripten    = current_dir .. "emscripten.lua",
}

-- @brief Get Vulkan SDK Path.
--
-- @return Returns Vulkan SDK Path.
local GetVulkanSDKPath = function()

    -- Search in Env first.
    local sdk_path = os.getenv("VULKAN_SDK") or ""
    local include_dir = (os.target() == "windows") and "Include" or "include"

    if sdk_path ~= "" then
        return sdk_path .. "/" .. include_dir
    end

    local version = "1.4.321.1"

    -- Default Vulkan Path.
    local default_paths = {
        windows = "C:/VulkanSDK/" .. version .. "/Include",
        linux   = os.getenv("HOME") .. "/VulkanSDK/" .. version .. "/x86_64/include",
        macosx  = ""
    }

    return default_paths[os.target()] or ""

end

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

-- @brief Get AdaptiveCpp Path.
--
-- @return Returns AdaptiveCpp Path.
local GetAdaptiveCppPath = function()

    local paths = {
        windows = "C:/AdaptiveCpp",
        linux   = "",
        macosx  = ""
    }

    return paths[os.target()] or ""

end

-- @brief Get Sub Vendor LibraryDirs.
--
-- @return Returns Sub Vendor LibraryDirs.
local GetSubVendorLibraryDirs = function()

    return loadfile(sub_vendor[os.target()])().GetLibraryDirs(module.includes) or {}

end

-- @brief Get Sub Vendor Libraries.
--
-- @return Returns Sub Vendor Libraries.
local GetSubVendorLibraries = function()

    return loadfile(sub_vendor[os.target()])().GetLibraries() or {}

end

-- Includes
local includes                        = {
    ["Neptune"]                       = solution_root .. "/Neptune/src",                                               -- Include: Neptune
    ["NeptuneShader"]                 = solution_root .. "/Neptune/assets/Shaders/src",                                -- Include: NeptuneShader
    ["emscripten"]                    = GetEmsdkPath() .. "/upstream/emscripten/cache/sysroot/include/",               -- Include: emscripten
    ["emscripten_glfw"]               = solution_root .. "/Neptune/vendor/emscripten-glfw/",                           -- Include: emscripten-glfw
    ["emdawnwebgpu"]                  = solution_root .. "/Neptune/vendor/emdawnwebgpu/webgpu/include",                -- Include: emdawnwebgpu
    ["GLFW"]                          = solution_root .. "/Neptune/vendor/GLFW/include",                               -- Include: GLFW
    ["VulkanSDK"]                     = GetVulkanSDKPath(),                                                            -- Include: VulkanSDK
    ["glm"]                           = solution_root .. "/Neptune/vendor/glm",                                        -- Include: glm
    ["vma"]                           = solution_root .. "/Neptune/vendor/vma/include",                                -- Include: vma
    ["Glad"]                          = solution_root .. "/Neptune/vendor/Glad/include",                               -- Include: Glad
    ["stb_image"]                     = solution_root .. "/Neptune/vendor/stb_image",                                  -- Include: stb_image
    ["ImGui"]                         = solution_root .. "/Neptune/vendor/imgui",                                      -- Include: ImGui
    ["entt"]                          = solution_root .. "/Neptune/vendor/entt/include",                               -- Include: entt
    ["yaml_cpp"]                      = solution_root .. "/Neptune/vendor/yaml-cpp/include",                           -- Include: yaml_cpp
    ["rapidyaml"]                     = solution_root .. "/Neptune/vendor/rapidyaml",                                  -- Include: rapidyaml
    ["ImPlot"]                        = solution_root .. "/Neptune/vendor/implot",                                     -- Include: ImPlot
    ["spdlog"]                        = solution_root .. "/Neptune/vendor/spdlog/include",                             -- Include: spdlog
    ["ImGuizmo"]                      = solution_root .. "/Neptune/vendor/ImGuizmo",                                   -- Include: ImGuizmo
    ["tracy"]                         = solution_root .. "/Neptune/vendor/tracy/public",                               -- Include: tracy
    ["IconFontCppHeaders"]            = solution_root .. "/Neptune/vendor/IconFontCppHeaders",                         -- Include: IconFontCppHeaders
    ["shaderc"]                       = solution_root .. "/Neptune/vendor/shaderc",                                    -- Include: shaderc
    ["glslang"]                       = GetVulkanSDKPath() ..  "/glslang",                                             -- Include: glslang
    ["WinPixEventRuntime"]            = solution_root .. "/packages/WinPixEventRuntime.1.0.240308001/include",         -- Include: WinPixEventRuntime
    ["AdaptiveCpp"]                   = GetAdaptiveCppPath() .. "/include",                                            -- Include: AdaptiveCpp
    ["googletest"]                    = solution_root .. "/UnitTest/vendor/googletest/googletest/include",             -- Include: googletest
    ["googlemock"]                    = solution_root .. "/UnitTest/vendor/googletest/googlemock/include",             -- Include: googlemock
}
module.includes                       = includes

-- Library Directories
module.library_dirs                   = GetSubVendorLibraryDirs()

-- Library Directories
module.libraries                      = GetSubVendorLibraries()

-- Nuget Dependencies
module.nugets                         = {
    ["DirectX12AgilitySDK"]           = "Microsoft.Direct3D.D3D12:1.618.5",                                            -- Nugets package: Direct3D12
    ["WinPixEventRuntime"]            = "WinPixEventRuntime:1.0.240308001",                                            -- Nugets package: WinPixEventRuntime
}

-- Desktop Third Party Projects
module.third_party_projects_desktops  = {
	["GLFW"]                          = solution_root .. "/Neptune/vendor/GLFW",                                       -- Dependency: GLFW
	["Glad"]                          = solution_root .. "/Neptune/vendor/Glad",                                       -- Dependency: Glad
    ["shaderc"]                       = solution_root .. "/Neptune/vendor/shaderc",                                    -- Dependency: shaderc
}

-- Third Party Projects
module.third_party_projects           = {
	["imgui"]                         = solution_root .. "/Neptune/vendor/imgui",                                      -- Dependency: imgui
	["yaml-cpp"]                      = solution_root .. "/Neptune/vendor/yaml-cpp",                                   -- Dependency: yaml-cpp
	["implot"]                        = solution_root .. "/Neptune/vendor/implot",                                     -- Dependency: implot
    ["tracy"]                         = solution_root .. "/Neptune/vendor/tracy",                                      -- Dependency: tracy
    ["googletest"]                    = solution_root .. "/UnitTest/vendor/googletest",                                -- Dependency: googletest
}

-- @brief Load Third Party Projects.
module.LoadThirdPartyProjects = function()

    -- Project Dependencies.
    group "Dependencies"
    if os.target() ~= "emscripten" then
        for name, path in pairs(module.third_party_projects_desktops) do
            include(path)
        end
    end
    for name, path in pairs(module.third_party_projects) do
        include(path)
    end
    group ""

end

return module