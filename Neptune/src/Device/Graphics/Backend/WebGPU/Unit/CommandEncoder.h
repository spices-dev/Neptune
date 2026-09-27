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
		* @param[in] desc WGPURenderPassDescriptor.
		* 
		* @return Returns WGPURenderPassEncoder.
		*/
		WGPURenderPassEncoder BeginRenderPass(const WGPURenderPassDescriptor& desc) const;
		
		/**
		* @brief Begin ComputePass.
		*
		* @param[in] desc WGPUComputePassDescriptor.
		* 
		* @return Returns WGPUComputePassEncoder.
		*/
		WGPUComputePassEncoder BeginComputePass(const WGPUComputePassDescriptor& desc) const;
		
		/**
		* @brief Copy Texture To Texture.
		* 
		* @param[in] source WGPUTexelCopyTextureInfo.
		* @param[in] destination WGPUTexelCopyTextureInfo.
		* @param[in] copySize WGPUExtent3D.
		*/
		void CopyTextureToTexture(const WGPUTexelCopyTextureInfo& source, const WGPUTexelCopyTextureInfo& destination, const WGPUExtent3D& copySize) const;
		
		/**
		* @brief Copy Buffer To Buffer.
		* 
		* @param[in] source WGPUBuffer.
		* @param[in] sourceOffset .
		* @param[in] destination WGPUBuffer.
		* @param[in] destinationOffset .
		* @param[in] size .
		*/
		void CopyBufferToBuffer(WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) const;
	};
}

#endif