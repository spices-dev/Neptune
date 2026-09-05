/**
* @file EditorWorld.cpp.
* @brief The EditorWorld Class Implementation.
* @author Spices.
*/

#include "EditorWorld.h"
#include "Layout.h"
#include "Scripts/VideoPlayer.h"
#include "Scripts/RHICapturer.h"
#include "Scripts/CameraController.h"

#include <World/Scene/Scene.h>
#include <World/Entity/Entity.h>
#include <World/Component/TransformComponent.h>
#include <World/Component/ScriptComponent.h>
#include <World/Component/SOPComponent.h>
#include <World/Component/CameraComponent.h>
#include <Scripts/NativeScripts/EngineClock.h>
#include <Asset/SOP/GS3D.h>
#include <GamePlay/Camera/Camera.h>
#include <Data/Transform.h>

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
            auto entity = scene->Create("camera");
            
            auto& camera = entity.AddComponent<CameraComponent>(Camera::CreatePerspective({}));
            
            auto& transform = entity.AddComponent<TransformComponent>();
            
            transform.GetModel()->position = { 30.0f, 6.0f, 15.0f };
            transform.GetModel()->rotation = {8.0f, -90.0f, 0.0f};
            
            auto& scripts = entity.AddComponent<ScriptComponent>();
            
            scripts.AddScript(CreateSP<CameraController>(camera.GetModel(), transform.GetModel()));
        }
        
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
            auto gs3d = CreateSP<SOP::GS3D>("C:/Users/spices/Downloads/flowers_1/flowers_1.ply");
            gs3d->LoadFromDisk();
            
            auto entity = scene->Create("gs3d");
            entity.AddComponent<SOPComponent>(gs3d);
        }
    }
}
