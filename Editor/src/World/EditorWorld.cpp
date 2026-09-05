/**
* @file EditorWorld.cpp.
* @brief The EditorWorld Class Implementation.
* @author Spices.
*/

#include "EditorWorld.h"
#include "Layout.h"
#include "Scripts/VideoPlayer.h"
#include "Scripts/RHICapturer.h"

#include <World/Scene/Scene.h>
#include <World/Entity/Entity.h>
#include <World/Component/TransformComponent.h>
#include <World/Component/ScriptComponent.h>
#include <World/Component/SOPComponent.h>
#include <Scripts/NativeScripts/EngineClock.h>
#include <Resource/SOP/GS3D.h>

namespace Neptune::Editor {

    void EditorWorld::OnAttached()
    {
        NEPTUNE_PROFILE_ZONE

        World::OnAttached();

        CreateExampleScene();

        SetFlag(WorldMarkBit::DynamicScriptTick, true);
        SetFlag(WorldMarkBit::DynamicScriptEvent, true);
    }

    void EditorWorld::OnDetached()
    {
        NEPTUNE_PROFILE_ZONE

        World::OnDetached();
    }

    void EditorWorld::OnLayout() const
    {
        NEPTUNE_PROFILE_ZONE
        
        Layout::OnLayout();
    }
    
    void EditorWorld::CreateExampleScene()
    {
        NEPTUNE_PROFILE_ZONE

        const auto scene = CreateScene("main_level");

        auto& scriptComponent = scene->GetComponent<ScriptComponent>(scene->GetRoot());

        scriptComponent.AddScript(CreateSP<EngineClock>(scene));

        {
            auto entity = scene->Create("cube");
            entity.AddComponent<TransformComponent>();
        }

        {
            auto entity = scene->Create("plane");
            entity.AddComponent<TransformComponent>();
        }
        
        /*{
            auto entity = scene->Create("video_plane");
            auto& component = entity.AddComponent<ScriptComponent>();
            
            component.AddScript(CreateSP<RHICapturer>());
            component.AddScript(CreateSP<VideoPlayer>("C:/Users/spices/Desktop/hevc_8k60P_bilibili_1.mp4"));
        }*/
        
        {
            auto gs3d = CreateSP<SOP::GS3D>("xx.asset");
            gs3d->LoadFromDisk();
            
            auto entity = scene->Create("gs3d");
            entity.AddComponent<SOPComponent>(gs3d);
        }
    }
}
