/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::CommandBuffer Class.
    * This class defines the Metal::Unit::CommandBuffer behaves.
    */
    class CommandBuffer : public Unit<MTLCommandBuffer>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        CommandBuffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~CommandBuffer() override;
        
        /**
        * @brief Create CommandBuffer.
        * 
        * @param[in] commandQueue MTLCommandQueue.
        */
        void CreateCommandBuffer(MTLCommandQueue commandQueue);
    };
}

#endif