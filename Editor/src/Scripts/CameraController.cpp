/**
* @file CameraController.cpp.
* @brief The CameraController Class Implementation.
* @author Spices.
*/

#include "CameraController.h"

#include <GamePlay/Camera/Camera.h>
#include <Core/Input/Input.h>
#include <Core/Input/MouseButtonCodes.h>
#include <Data/Transform.h>
#include <GamePlay/Camera/OrthographicCamera.h>
#include <GamePlay/Camera/PerspectiveCamera.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Neptune::Editor {
	
    void CameraController::OnTick()
    {
        NEPTUNE_PROFILE_ZONE
        
        if (Input::IsKeyPressed(Key::LeftAlt))
        {
            const glm::vec2& mouse { Input::GetMouseX(), Input::GetMouseY() };
            const glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
            m_InitialMousePosition = mouse;
			
            if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
            {
                MousePan(delta);    
            }
            else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
            {
                MouseRotate(delta); 
            }
            else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
            {
                MouseZoom(delta.y); 
            }

            UpdateView();
        }
    }
    
    void CameraController::OnEvent(Event& e)
    {
        NEPTUNE_PROFILE_ZONE
        
        EventDispatcher dispatcher(e);
        
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnMouseScroll));
        dispatcher.Dispatch<ViewResizeEvent>(BIND_EVENT_FN(CameraController::OnSlateResized));
    }
    
    bool CameraController::OnMouseScroll(MouseScrolledEvent& e)
    {
        NEPTUNE_PROFILE_ZONE

        const float ratio = static_cast<float>(m_ViewportWidth) / static_cast<float>(m_ViewportHeight);

        const float delta = e.GetYOffset() * 0.1f;

        m_ZoomLevel += delta;
        m_ZoomLevel  = std::max(m_ZoomLevel, 0.2f);

        if (m_Camera->GetProjectionType() == ProjectionType::Orthographic)
        {
            auto p = std::static_pointer_cast<OrthographicCamera>(m_Camera);
            
            auto& param            = p->GetParam();
            param.left             = -ratio * m_ZoomLevel;
            param.right            = ratio * m_ZoomLevel;
            param.top              = -m_ZoomLevel;
            param.bottom           = m_ZoomLevel;
            param.nearPlane        = 0.001f;
            param.farPlane         = 100000.0f;
        }

        MouseZoom(delta);
        
        UpdateView();

        return false;
    }
    
    bool CameraController::OnSlateResized(ViewResizeEvent& e)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_ViewportWidth  = e.GetWidth();
        m_ViewportHeight = e.GetHeight();
        
        const float ratio = static_cast<float>(m_ViewportWidth) / static_cast<float>(m_ViewportHeight);

        switch (m_Camera->GetProjectionType())
        {
            case ProjectionType::Perspective:
            {
                auto p = std::static_pointer_cast<PerspectiveCamera>(m_Camera);
                
                p->GetParam().aspectRatio = ratio;
                
                break;
            }
            case ProjectionType::Orthographic:
            {
                auto p = std::static_pointer_cast<OrthographicCamera>(m_Camera);
            
                auto& param            = p->GetParam();
                param.left             = -ratio * m_ZoomLevel;
                param.right            = ratio * m_ZoomLevel;
                param.top              = -m_ZoomLevel;
                param.bottom           = m_ZoomLevel;
                param.nearPlane        = 0.001f;
                param.farPlane         = 100000.0f;
                
                break;
            }
        }
        
        return false;
    }

    void CameraController::MousePan(const glm::vec2& delta)
    {
        NEPTUNE_PROFILE_ZONE
		
        auto [xSpeed, ySpeed] = PanSpeed();
        m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
        m_FocalPoint += -GetUpDirection() * delta.y * ySpeed * m_Distance;
    }

    void CameraController::MouseRotate(const glm::vec2& delta) const
    {
        NEPTUNE_PROFILE_ZONE
		
        glm::vec3 rot = m_Transform->rotation;
        const float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;

        rot.y -= glm::degrees(yawSign * delta.x * RotationSpeed());
        rot.x += glm::degrees(delta.y * RotationSpeed());

        m_Transform->rotation = rot;
    }

    void CameraController::MouseZoom(const float& delta)
    {
        NEPTUNE_PROFILE_ZONE
		
        m_Distance += delta * ZoomSpeed();
        
        if (m_Distance < 1.0f)
        {
            m_FocalPoint += GetForwardDirection();
            
            m_Distance = 1.0f;
        }
    }

    std::pair<float, float> CameraController::PanSpeed() const
    {
        NEPTUNE_PROFILE_ZONE
		
        const float x = std::min(static_cast<float>(m_ViewportWidth) / 1000.0f, 2.4f); // max = 2.4f
        
        float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

        const float y = std::min(static_cast<float>(m_ViewportHeight) / 1000.0f, 2.4f); // max = 2.4f
        
        float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

        return { xFactor, yFactor };
    }

    float CameraController::RotationSpeed() const
    {
        NEPTUNE_PROFILE_ZONE
		
        return 0.8f;
    }

    float CameraController::ZoomSpeed() const
    {
        NEPTUNE_PROFILE_ZONE
		
        float distance = m_Distance * 0.2f;
        
        distance = std::max(distance, 0.0f);
        
        float speed = distance * distance;
        
        speed = std::min(speed, 100.0f); // max speed = 100
        
        return speed;
    }

    void CameraController::UpdateView() const
    {
        NEPTUNE_PROFILE_ZONE
		
        const glm::vec3 pos = CalculatePosition();
        
        m_Transform->position = pos;
    }
    
    glm::vec3 CameraController::CalculatePosition() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_FocalPoint - GetForwardDirection() * m_Distance;
    }
    
    glm::vec3 CameraController::GetUpDirection() const
    {
        NEPTUNE_PROFILE_ZONE
		
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, -1.0f, 0.0f));
    }

    glm::vec3 CameraController::GetRightDirection() const
    {
        NEPTUNE_PROFILE_ZONE
		
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::vec3 CameraController::GetForwardDirection() const
    {
        NEPTUNE_PROFILE_ZONE
		
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    glm::quat CameraController::GetOrientation() const
    {
        NEPTUNE_PROFILE_ZONE
		
        const glm::vec3& rot = m_Transform->rotation;
        
        return glm::quat({ glm::radians(rot.x), glm::radians(rot.y), glm::radians(rot.z) });
    }
}
