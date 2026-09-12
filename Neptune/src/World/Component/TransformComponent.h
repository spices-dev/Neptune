/**
* @file TransformComponent.h.
* @brief The TransformComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Core/Math/Transform.h"
#include "Core/Container/BitSet.h"

namespace Neptune {

    /**
    * @brief TransformComponent Class.
    * This class defines the specific behaves of TransformComponent.
    */
    class TransformComponent : public Component<SP<Data::Transform>>
    {
    public:

        enum TransformComponentBits : uint8_t
        {
            Clean = 0,
            NeedUpdateTLAS,
            
            Count
        };

    public:

        /**
        * @brief Constructor Function.
        */
        TransformComponent() : Component(CreateSP<Data::Transform>()) {}

        /**
        * @brief Destructor Function.
        */
        ~TransformComponent() override = default;

        /**
        * @brief Get the modelMatrix variable.
        * 
        * @return Returns the modelMatrix variable.
        */
        const glm::mat4& GetModelMatrix() { m_ModelMatrix = ToMatrix(*GetModel()); return m_ModelMatrix; }

        /**
        * @brief Get WorldMarkFlags this frame.
        * 
        * @return Returns the TransformComponentFlags.
        */
        const Container::BitSet<TransformComponentBits>& GetMarker() const { return m_Marker; }

        /**
        * @brief Mark TransformComponentFlags with flags.
        * 
        * @param[in] flags In flags.
        */
        void Mark(const Container::BitSet<TransformComponentBits>& flags) { m_Marker |= flags; }

        /**
        * @brief Mark TransformComponentFlags with flags.
        * 
        * @param[in] bit In flags.
        */
        void Mark(const TransformComponentBits& bit) { m_Marker.Set(bit, true); }

        /**
        * @brief Clear TransformComponentFlags with flags.
        * 
        * @param[in] flags In flags.
        */
        void ClearMarkerWithBits(const Container::BitSet<TransformComponentBits>& flags) { m_Marker ^= flags; }

    private:

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);   // @brief The modelMatrix this component handled.

        Container::BitSet<TransformComponentBits> m_Marker{ Clean };  // @brief World State this frame.
    };
}