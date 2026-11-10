/**
* @file GarbageCollection.h.
* @brief The GarbageCollection Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Frontend/Infrastructure/GarbageCollection.h"

namespace Neptune::Direct3D12 {

    using IGarbageCollection = IInfrastructure<class GarbageCollection, EInfrastructure::GarbageCollection>;

    /**
    * @brief Direct3D12::GarbageCollection Class.
    * This class defines the Direct3D12::GarbageCollection behaves.
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