/**
* @file DataGraphPipelineSession.h.
* @brief The DataGraphPipelineSession Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::DataGraphPipelineSession Class.
    * This class defines the Vulkan::Unit::DataGraphPipelineSession behaves.
    */
    class DataGraphPipelineSession : public Unit<VkDataGraphPipelineSessionARM, VkObjectType::VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DataGraphPipelineSession() = default;

        /**
        * @brief Destructor Function.
        */
        ~DataGraphPipelineSession() override;

        /**
        * @brief Create DataGraphPipelineSession.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkDataGraphPipelineSessionCreateInfoARM.
        */
        void CreateDataGraphPipelineSession(VkDevice device, const VkDataGraphPipelineSessionCreateInfoARM& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif