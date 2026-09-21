/**
* @file Input.h.
* @brief The Input Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Window/Enum.h"

namespace Neptune {

    /**
    * @brief This Class Is a wrapper of Platform Specific Input Query.
    */
    class Input : public NonCopyable
    {
    public:
        
        /**
        * @brief Create Input.
        * 
        * @param[in] implement WindowImplement.
        */
        static void Create(WindowImplement implement);
        
    public:

        /**
        * @brief Constructor Function.
        */
        Input() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Input() = default;

        /**
        * @brief Query If given Key is Pressed.
        * 
        * @param[in] keycode In Key Code.
        * 
        * @return Returns true if given Key is Pressed.
        */
        static bool IsKeyPressed(const int& keycode);

        /**
        * @brief Query If given Mouse Button is Pressed.
        * 
        * @param[in] button In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        static bool IsMouseButtonPressed(const int& button);

        /**
        * @brief Query Mouse Position in Windows.
        * 
        * @return Returns the pair of Mouse Position in Windows.
        */
        static std::pair<float, float> GetMousePosition();

        /**
        * @brief Query Mouse X Position in Windows.
        * 
        * @return Returns the Mouse X Position in Windows.
        */
        static float GetMouseX();

        /**
        * @brief Query Mouse Y Position in Windows.
        * 
        * @return Returns the Mouse Y Position in Windows.
        */
        static float GetMouseY();

    protected:

        /**
        * @brief Query If given Key is Pressed.
        * Interface for platform Implementation.
        * 
        * @param[in] keycode In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        virtual bool IsKeyPressedImpl(const int& keycode) = 0;

        /**
        * @brief Query If given Mouse Button is Pressed.
        * Interface for platform Implementation.
        * 
        * @param[in] button In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        virtual bool IsMouseButtonPressedImpl(const int& button) = 0;

        /**
        * @brief Query Mouse Position in Windows.
        * Interface for platform Implementation.
        * 
        * @return Returns the pair of Mouse Position in Windows.
        */
        virtual std::pair<float, float> GetMousePositionImpl() = 0;

        /**
        * @brief Query Mouse X Position in Windows.
        * Interface for platform Implementation.
        * 
        * @return Returns the Mouse X Position in Windows.
        */
        virtual float GetMouseXImpl() = 0;

        /**
        * @brief Query Mouse Y Position in Windows.
        * Interface for platform Implementation.
        * 
        * @return Returns the Mouse Y Position in Windows.
        */
        virtual float GetMouseYImpl() = 0;
    };

}