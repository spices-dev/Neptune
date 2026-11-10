/**
* @file GarbageCollection.h.
* @brief The GarbageCollection Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Frontend/Infrastructure/GarbageCollection.h"

namespace Neptune::WebGPU {

    using IGarbageCollection = IInfrastructure<class GarbageCollection, EInfrastructure::GarbageCollection>;

    /**
    * @brief WebGPU::GarbageCollection Class.
    * This class defines the WebGPU::GarbageCollection behaves.
    */
    class GarbageCollection : public Infrastructure, public Graphic::GarbageCollection
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        GarbageCollection(Context& context, EInfrastructure e) : Infrastructure(context, e), Graphic::GarbageCollection() {}

        /**
        * @brief Destructor Function.
        */
        ~GarbageCollection() override = default;
    };
}

#endif