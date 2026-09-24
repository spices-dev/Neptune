/**
* @file QuerySet.h.
* @brief The QuerySet Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::QuerySet Class.
    * This class defines the WebGPU::Unit::QuerySet behaves.
    */
    class QuerySet : public Unit<WGPUQuerySet>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        QuerySet() = default;

        /**
        * @brief Destructor Function.
        */
        ~QuerySet() override;

        /**
        * @brief Create QuerySet.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUQuerySetDescriptor.
        */
        void CreateQuerySet(WGPUDevice device, const WGPUQuerySetDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif