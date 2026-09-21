/**
* @file InputImpl.h.
* @brief The InputImpl Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#include "Core/Core.h"
#include "Core/Input/Input.h"

namespace Neptune::InputNone {

    /**
    * @brief This Class Is none Specific Input Class.
    */
    class InputImpl : public Input
    {
    protected:

        /**
        * @brief Query If given Key is Pressed.
        * 
        * @param[in] keycode In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        bool IsKeyPressedImpl(const int& keycode) override { return false; }

        /**
        * @brief Query If given Mouse Button is Pressed.
        * 
        * @param[in] button In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        bool IsMouseButtonPressedImpl(const int& button) override { return false; }

        /**
        * @brief Query Mouse Position in Windows.
        * 
        * @return Returns the pair of Mouse Position in Windows.
        */
        std::pair<float, float> GetMousePositionImpl() override { return { 0.0f, 0.0f }; }

        /**
        * @brief Query Mouse X Position in Windows.
        * 
        * @return Returns the Mouse X Position in Windows.
        */
        float GetMouseXImpl() override { return 0.0f; }

        /**
        * @brief Query Mouse Y Position in Windows.
        * 
        * @return Returns the Mouse Y Position in Windows.
        */
        float GetMouseYImpl() override { return 0.0f; }
    };
}