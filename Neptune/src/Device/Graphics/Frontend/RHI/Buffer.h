/**
* @file Buffer.h.
* @brief The Buffer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {
	
    using RHIBuffer = RHI<ERHI::Buffer>;

    /**
    * @brief Specialization of RHIBuffer::Impl
    */
    template<>
    class RHIBuffer::Impl
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Impl() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Impl() = default;
    };

    /**
    * @brief RHI of ERHI::Buffer
    */
    class Buffer : public RHIBuffer
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Buffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override = default;

    };
}