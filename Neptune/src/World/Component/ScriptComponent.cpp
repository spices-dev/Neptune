/**
* @file ScriptComponent.cpp.
* @brief The ScriptComponent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ScriptComponent.h"
#include "Scripts/ScriptInterface.h"
#include <ranges>

namespace Neptune {

    void ScriptComponent::AddScript(const SP<ScriptInterface>& script)
    {
        NEPTUNE_PROFILE_ZONE

        if (GetModel().contains(script->GetFileString()))
        {
            NEPTUNE_LOG_CORE(W) << "Script is existing on component.";
            return;
        }

        script->OnAttached();

        GetModel()[script->GetFileString()] = script;
    }

    void ScriptComponent::RemoveScript(const std::string& name)
    {
        NEPTUNE_PROFILE_ZONE

        if (!GetModel().contains(name))
        {
            NEPTUNE_LOG_CORE(W) << "Script is not existing on component.";
            return;
        }

        GetModel()[name]->OnDetached();

        GetModel().erase(name);
    }
    
    void ScriptComponent::OnTick() const
    {
        NEPTUNE_PROFILE_ZONE

        for (const auto& script : GetModel() | std::views::values)
        {
            script->OnTick();
        }
    }

    void ScriptComponent::OnEvent(Event& e) const
    {
        NEPTUNE_PROFILE_ZONE

        for (const auto& script : GetModel() | std::views::values)
        {
            script->OnEvent(e);
        }
    }

    void ScriptComponent::OnComponentDetached()
    {
        NEPTUNE_PROFILE_ZONE

        for (const auto& script : GetModel() | std::views::values)
        {
            script->OnDetached();
        }
    }
    
}