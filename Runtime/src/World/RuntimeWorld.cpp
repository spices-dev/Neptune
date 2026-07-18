/**
* @file RuntimeWorld.cpp.
* @brief The RuntimeWorld Class Implementation.
* @author Spices.
*/

#include "RuntimeWorld.h"
#include <World/Scene/Scene.h>
#include <World/Component/ScriptComponent.h>
#include <Scripts/NativeScripts/EngineClock.h>

namespace Neptune::Runtime {
    
    void RuntimeWorld::OnAttached()
    {
        NEPTUNE_PROFILE_ZONE

        World::OnAttached();

        const auto scene = CreateScene("main_level");
        
        auto& scriptComponent = scene->GetComponent<ScriptComponent>(scene->GetRoot());

        scriptComponent.AddScript(CreateSP<EngineClock>(scene));

        SetFlag(WorldMarkBit::DynamicScriptTick, true);
        SetFlag(WorldMarkBit::DynamicScriptEvent, true);
    }

    void RuntimeWorld::OnDetached()
    {
        NEPTUNE_PROFILE_ZONE

        World::OnDetached();
    }
}
