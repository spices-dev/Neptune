/**
* @file CameraController.h.
* @brief The CameraController Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <Scripts/NativeScripts/NativeScript.h>
#include <Core/Event/KeyEvent.h>
#include <Core/Event/MouseEvent.h>
#include <Core/Event/ViewEvent.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

namespace Neptune {
	
	class Camera;
}

namespace Neptune::Data {
	
	class Transform;
}

namespace Neptune::Editor {
	
	/**
	* @brief CameraController Script.
	*/
	class CameraController : public NativeScript
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		CameraController(const SP<Camera>& camera, const SP<Data::Transform>& transform) : m_Camera(camera), m_Transform(transform) {}
		
		/**
		* @brief Destructor Function.
		*/
		~CameraController() override = default;

		/**
		* @brief This interface defines the behave on specific component tick every frame.
		*/
		void OnTick() override;
		
		/**
		* @brief This interface defines the behave on specific component event happened.
		*
		* @param[in] e Event.
		*/
		void OnEvent(Event& e) override;

	private:
		
		/**
		* @brief Event OnMouseScroll.
		* 
		* @param[in] e Event Wrapper.
		* 
		* @return true if block event.
		*/
		bool OnMouseScroll(MouseScrolledEvent& e);
		
		/**
		* @brief Event OnWindowResized.
		* 
		* @param[in] e Event Wrapper.
		* 
		* @return true if block event.
		*/
		bool OnSlateResized(ViewResizeEvent& e);
		
		/**
		* @brief Calculate Camera Drag.
		* 
		* @param[in] delta Mouse position delta on viewport during frames.
		*/
		void MousePan(const glm::vec2& delta);

		/**
		* @brief Calculate Camera Rotate.
		* 
		* @param[in] delta Mouse position delta on viewport during frames.
		*/
		void MouseRotate(const glm::vec2& delta) const;

		/**
		* @brief Calculate Camera Zoom.
		* 
		* @param[in] delta Mouse position delta y on viewport during frames.
		*/
		void MouseZoom(const float& delta);

		/**
		* @brief Calculate Camera Drag speed.
		* 
		* @return Returns the camera drag speed in x direction and y direction.
		*/
		std::pair<float, float> PanSpeed() const;

		/**
		* @brief Calculate Camera Rotate speed.
		* 
		* @return Returns the speed camera rotate.
		*/
		float RotationSpeed() const;

		/**
		* @brief Calculate Camera Zoom speed.
		* 
		* @return Returns the speed camera zoom.
		*/
		float ZoomSpeed() const;

		/**
		* @brief Setting camera transform position.
		* 
		* We already set rotation in MouseRotate().
		*/
		void UpdateView() const;
		
		/**
		* @brief Calculate camera transform position.
		* 
		* @return Returns camera transform position.
		*/
		glm::vec3 CalculatePosition() const;
		
		/**
		* @brief Get Camera Up(y) Direction.
		* 
		* @return The Camera Up(y) Direction.
		*/ 
		glm::vec3 GetUpDirection() const;

		/**
		* @brief Get Camera Right(x) Direction.
		* 
		* @return The Camera Right(x) Direction.
		*/
		glm::vec3 GetRightDirection() const;

		/**
		* @brief Get Camera Forward(z) Direction.
		* 
		* @return The Camera Forward(z) Direction.
		*/
		glm::vec3 GetForwardDirection() const;

		/**
		* @brief Get Camera quaternion rotation.
		* 
		* @return The Camera quaternion rotation.
		*/
		glm::quat GetOrientation() const;
		
	private:

		SP<Camera> m_Camera;                                    // @brief Camera.
		SP<Data::Transform> m_Transform;                        // @brief Transform.
		uint32_t m_ViewportWidth = 1920;                        // @brief The Viewport Width.
		uint32_t m_ViewportHeight = 1080;                       // @brief The Viewport Height.
		float m_ZoomLevel = 1.0f;                               // @brief Zoom Level.
		float m_Distance = 10.0f;                               // @brief Camera spring arm.
		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };      // @brief Mouse position.
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };          // @brief The focus point.
	};
}