/**
* @file Layer.h.
* @brief The Layer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Metal/Unit/Layer.h"

namespace Neptune::Metal {

    using ILayer = IInfrastructure<class Layer, EInfrastructure::Layer>;

    /**
    * @brief Metal::Layer Class.
    * This class defines the Metal::Layer behaves.
    */
    class Layer : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] count Semaphore Spare Count.
        */
        Layer(Context& context, EInfrastructure e, uint32_t count);

        /**
        * @brief Destructor Function.
        */
        ~Layer() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Layer::Handle& Handle() const { return m_Layer.GetHandle(); }

        /**
        * @brief Get Next Drawable.
        */
        void NextDrawable();

    private:
            
        /**
        * @brief Create Layer.
        * 
        * @param[in] count Layer Drawable Count.
        */
        void Create(uint32_t count);

    private:

        Unit::Layer m_Layer;  // @brief this Layer.
    };
	
}

#endif