/**
* @file PipelineCache.h.
* @brief The PipelineCache Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::PipelineCache Class.
    * This class defines the Vulkan::Unit::PipelineCache behaves.
    */
    class PipelineCache : public Unit<VkPipelineCache, VkObjectType::VK_OBJECT_TYPE_PIPELINE_CACHE>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        PipelineCache() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~PipelineCache() override;

        /**
        * @brief Create CommandPool.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkPipelineCacheCreateInfo.
        */
        void CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif