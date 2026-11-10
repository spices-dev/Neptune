/**
* @file GarbageCollection.h.
* @brief The GarbageCollection Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Device/Graphics/Backend/Metal/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Frontend/Infrastructure/GarbageCollection.h"

namespace Neptune::Metal {

    using IGarbageCollection = IInfrastructure<class GarbageCollection, EInfrastructure::GarbageCollection>;

    /**
    * @brief Metal::GarbageCollection Class.
    * This class defines the Metal::GarbageCollection behaves.
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