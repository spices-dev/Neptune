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
    sdk_path = sdk_path:gsub("\\", "/")

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
    ["Neptune"]                       = solution_root .. "/Neptune/src",                                                            -- Include: Neptune
    ["NeptuneShader"]                 = solution_root .. "/Neptune/assets/Shaders/src",                                             -- Include: NeptuneShader
    ["emscripten"]                    = GetEmsdkPath() .. "/upstream/emscripten/cache/sysroot/include/",                            -- Include: emscripten
    ["emscripten_glfw"]               = solution_root .. "/Neptune/vendor/emscripten-glfw/",                                        -- Include: emscripten-glfw
    ["emdawnwebgpu"]                  = solution_root .. "/Neptune/vendor/emdawnwebgpu/webgpu/include",                             -- Include: emdawnwebgpu
    ["GLFW"]                          = solution_root .. "/Neptune/vendor/GLFW/include",                                            -- Include: GLFW
    ["VulkanSDK"]                     = GetVulkanSDKPath(),                                                                         -- Include: VulkanSDK
    ["glm"]                           = solution_root .. "/Neptune/vendor/glm",                                                     -- Include: glm
    ["vma"]                           = solution_root .. "/Neptune/vendor/vma/include",                                             -- Include: vma
    ["Glad"]                          = solution_root .. "/Neptune/vendor/Glad/include",                                            -- Include: Glad
    ["stb_image"]                     = solution_root .. "/Neptune/vendor/stb_image",                                               -- Include: stb_image
    ["ImGui"]                         = solution_root .. "/Neptune/vendor/imgui",                                                   -- Include: ImGui
    ["entt"]                          = solution_root .. "/Neptune/vendor/entt/include",                                            -- Include: entt
    ["yaml_cpp"]                      = solution_root .. "/Neptune/vendor/yaml-cpp/include",                                        -- Include: yaml_cpp
    ["rapidyaml"]                     = solution_root .. "/Neptune/vendor/rapidyaml",                                               -- Include: rapidyaml
    ["ImPlot"]                        = solution_root .. "/Neptune/vendor/implot",                                                  -- Include: ImPlot
    ["spdlog"]                        = solution_root .. "/Neptune/vendor/spdlog/include",                                          -- Include: spdlog
    ["ImGuizmo"]                      = solution_root .. "/Neptune/vendor/ImGuizmo",                                                -- Include: ImGuizmo
    ["tracy"]                         = solution_root .. "/Neptune/vendor/tracy/public",                                            -- Include: tracy
    ["IconFontCppHeaders"]            = solution_root .. "/Neptune/vendor/IconFontCppHeaders",                                      -- Include: IconFontCppHeaders
    ["DirectX12AgilitySDK"]           = solution_root .. "/Neptune/vendor/Microsoft.Direct3D.D3D12/build/native/include",           -- Include: DirectX12AgilitySDK
    ["DirectX_Headers"]               = solution_root .. "/Neptune/vendor/DirectX-Headers/include",                                 -- Include: DirectX-Headers
    ["WinPixEventRuntime"]            = solution_root .. "/Neptune/vendor/PixEvents/include",                                       -- Include: WinPixEventRuntime
    ["AdaptiveCpp"]                   = GetAdaptiveCppPath() .. "/include",                                                         -- Include: AdaptiveCpp
    ["googletest"]                    = solution_root .. "/UnitTest/vendor/googletest/googletest/include",                          -- Include: googletest
    ["googlemock"]                    = solution_root .. "/UnitTest/vendor/googletest/googlemock/include",                          -- Include: googlemock
}
module.includes                       = includes

-- Library Directories
module.library_dirs                   = GetSubVendorLibraryDirs()

-- Library Directories
module.libraries                      = GetSubVendorLibraries()

-- Nuget Dependencies
module.nugets                         = {
}

-- Desktop Third Party Projects
module.third_party_projects_desktops  = {
	["GLFW"]                          = solution_root .. "/Neptune/vendor/GLFW",                                       -- Dependency: GLFW
	["Glad"]                          = solution_root .. "/Neptune/vendor/Glad",                                       -- Dependency: Glad
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