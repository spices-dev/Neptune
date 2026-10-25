/**
* @file CommandSignature.h.
* @brief The CommandSignature Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

    /**
    * @brief Direct3D12::Unit::CommandSignature Class.
    * This class defines the Direct3D12::Unit::CommandSignature behaves.
    */
    class CommandSignature : public Unit<D3D12CommandSignature>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        CommandSignature() = default;

        /**
        * @brief Destructor Function.
        */
        ~CommandSignature() override;

        /**
        * @brief Create CommandSignature.
        * 
        * @param[in] device D3D12Device.
        * @param[in] desc D3D12_COMMAND_SIGNATURE_DESC.
        */
        void CreateCommandSignature(D3D12Device device, const D3D12_COMMAND_SIGNATURE_DESC& desc);

    };
}

#endif