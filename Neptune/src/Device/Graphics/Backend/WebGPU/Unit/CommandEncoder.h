/**
* @file CommandEncoder.h.
* @brief The CommandEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::CommandEncoder Class.
	* This class defines the WebGPU::Unit::CommandEncoder behaves.
	*/
	class CommandEncoder : public Unit<WGPUCommandEncoder>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandEncoder() = default;

		/**
		* @brief Destructor Function.
		*/
		~CommandEncoder() override;

		/**
		* @brief Create CommandEncoder.
		* 
		* @param[in] device WGPUDevice.
		* @param[in] desc WGPUCommandEncoderDescriptor.
		*/
		void CreateCommandEncoder(WGPUDevice device,  const WGPUCommandEncoderDescriptor& desc);
		
		/**
		* @brief Set Unit name.
		* 
		* @param[in] name Unit name.
		*/
		void SetName(const std::string& name) const;
		
		/**
		* @brief Begin RenderPass.
		*
		* @param[in] info WGPURenderPassDescriptor.
		* 
		* @return Returns WGPURenderPassEncoder.
		*/
		WGPURenderPassEncoder BeginRenderPass(const WGPURenderPassDescriptor& info) const;
	};
}

#endif