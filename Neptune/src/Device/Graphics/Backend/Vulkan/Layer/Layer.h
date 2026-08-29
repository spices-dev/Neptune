/**
* @file Layer.h.
* @brief The Layer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"

namespace Neptune::Vulkan::Layer {
    
    /**
    * @brief Enum of Layer State.
    */
    enum class ELayerState : uint8_t
    {
        Core = 0,       // @brief Core.
        Extent,         // @brief Extent.
    };
    
    /**
    * @brief Vulkan::Layer Class.
    * This class defines the Vulkan::Layer behaves.
    */
    class Layer
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state ELayerState.
        */
        explicit Layer(ELayerState state = ELayerState::Extent) : m_State(state) {}
        
        /**
        * @brief Destructor Function.
        */
        virtual ~Layer() = default;

        /**
        * @brief Get ELayerState.
        * 
        * @return Returns ELayerState.
        */
        ELayerState GetState() const { return m_State; }
        
    private:
        
        ELayerState m_State;                                             // @brief ELayerState.
    };
}

#endif