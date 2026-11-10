/**
* @file GarbageCollection.h.
* @brief The GarbageCollection Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Frontend/Infrastructure/GarbageCollection.h"

namespace Neptune::OpenGL {

    using IGarbageCollection = IInfrastructure<class GarbageCollection, EInfrastructure::GarbageCollection>;

    /**
    * @brief OpenGL::GarbageCollection Class.
    * This class defines the OpenGL::GarbageCollection behaves.
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