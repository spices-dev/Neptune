-- @file vendor.lua.
-- @brief Defines all Solutions Dependencies.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module                          = {
    ["Neptune"]                       = loadfile(current_dir .. "Neptune.lua")(),                                      -- Third Party: Neptune
    ["emscripten"]                    = loadfile(current_dir .. "emscripten.lua")(),                                   -- Third Party: emscripten
    ["emscripten_glfw"]               = loadfile(current_dir .. "emscripten-glfw.lua")(),                              -- Third Party: emscripten-glfw
    ["emdawnwebgpu"]                  = loadfile(current_dir .. "emdawnwebgpu.lua")(),                                 -- Third Party: emdawnwebgpu
    ["GLFW"]                          = loadfile(current_dir .. "GLFW.lua")(),                                         -- Third Party: GLFW
    ["Vulkan"]                        = loadfile(current_dir .. "Vulkan.lua")(),                                       -- Third Party: Vulkan
    ["glm"]                           = loadfile(current_dir .. "glm.lua")(),                                          -- Third Party: glm
    ["vma"]                           = loadfile(current_dir .. "vma.lua")(),                                          -- Third Party: vma
    ["Glad"]                          = loadfile(current_dir .. "Glad.lua")(),                                         -- Third Party: Glad
    ["stb_image"]                     = loadfile(current_dir .. "stb_image.lua")(),                                    -- Third Party: stb_image
    ["ImGui"]                         = loadfile(current_dir .. "ImGui.lua")(),                                        -- Third Party: ImGui
    ["entt"]                          = loadfile(current_dir .. "entt.lua")(),                                         -- Third Party: entt
    ["yaml_cpp"]                      = loadfile(current_dir .. "yaml-cpp.lua")(),                                     -- Third Party: yaml_cpp
    ["rapidyaml"]                     = loadfile(current_dir .. "rapidyaml.lua")(),                                    -- Third Party: rapidyaml
    ["ImPlot"]                        = loadfile(current_dir .. "ImPlot.lua")(),                                       -- Third Party: ImPlot
    ["spdlog"]                        = loadfile(current_dir .. "spdlog.lua")(),                                       -- Third Party: spdlog
    ["ImGuizmo"]                      = loadfile(current_dir .. "ImGuizmo.lua")(),                                     -- Third Party: ImGuizmo
    ["tracy"]                         = loadfile(current_dir .. "tracy.lua")(),                                        -- Third Party: tracy
    ["IconFontCppHeaders"]            = loadfile(current_dir .. "IconFontCppHeaders.lua")(),                           -- Third Party: IconFontCppHeaders
    ["Direct3D11"]                    = loadfile(current_dir .. "Direct3D11.lua")(),                                   -- Third Party: Direct3D11
    ["DirectX12AgilitySDK"]           = loadfile(current_dir .. "DirectX12AgilitySDK.lua")(),                          -- Third Party: DirectX12AgilitySDK
    ["DirectX_Headers"]               = loadfile(current_dir .. "DirectX-Headers.lua")(),                              -- Third Party: DirectX-Headers
    ["Vulkan_Headers"]                = loadfile(current_dir .. "Vulkan-Headers.lua")(),                               -- Third Party: Vulkan-Headers
    ["volk"]                          = loadfile(current_dir .. "volk.lua")(),                                         -- Third Party: volk
    ["WinPixEventRuntime"]            = loadfile(current_dir .. "WinPixEventRuntime.lua")(),                           -- Third Party: WinPixEventRuntime
    ["metal_cpp"]                     = loadfile(current_dir .. "metal-cpp.lua")(),                                    -- Third Party: metal-cpp
    ["AdaptiveCpp"]                   = loadfile(current_dir .. "AdaptiveCpp.lua")(),                                  -- Third Party: AdaptiveCpp
    ["ffmpeg"]                        = loadfile(current_dir .. "ffmpeg.lua")(),                                       -- Third Party: ffmpeg
    ["tinyply"]                       = loadfile(current_dir .. "tinyply.lua")(),                                      -- Third Party: tinyply
    ["nlohmannjson"]                  = loadfile(current_dir .. "nlohmannjson.lua")(),                                 -- Third Party: nlohmannjson
    ["miniz"]                         = loadfile(current_dir .. "miniz.lua")(),                                        -- Third Party: miniz
    ["RenderDoc"]                     = loadfile(current_dir .. "RenderDoc.lua")(),                                    -- Third Party: RenderDoc
    ["googletest"]                    = loadfile(current_dir .. "googletest.lua")(),                                   -- Third Party: googletest
}

-- @brief Load Third Party Projects.
module.LoadThirdPartyProjects = function()

    -- Project Dependencies.
    group "Dependencies"

    for name, third_party in pairs(module) do

        if type(third_party) ~= "table" then

            goto continue
            
        end

        if third_party.project then

            include(third_party.project)

        end

        ::continue::

    end
    
    group ""

end

return module