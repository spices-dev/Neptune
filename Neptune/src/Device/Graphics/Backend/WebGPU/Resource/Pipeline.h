/**
* @file Pipeline.h.
* @brief The Pipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/RenderPipeline.h"
#include "Device/Graphics/Backend/WebGPU/Unit/ComputePipeline.h"

#include <variant>

namespace Neptune::WebGPU::Resource {

	/**
	* @brief WebGPU::Pipeline Class.
	* This class defines the WebGPU::Pipeline behaves.
	*/
	class Pipeline : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Pipeline(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Pipeline() override = default;

		/**
		* @brief Create GraphicPipeline.
		* 
		* @param[in] desc WGPURenderPipelineDescriptor.
		*/
		void CreateRenderPipeline(const WGPURenderPipelineDescriptor& desc);

		/**
		* @brief Create ComputePipeline.
		* 
		* @param[in] desc WGPUComputePipelineDescriptor.
		*/
		void CreateComputePipeline(const WGPUComputePipelineDescriptor& desc);
		
	private:

		std::variant<
			UP<Unit::RenderPipeline>, 
			UP<Unit::ComputePipeline>
		> m_Pipeline;     // @brief Pipeline.

	};
}

#endif