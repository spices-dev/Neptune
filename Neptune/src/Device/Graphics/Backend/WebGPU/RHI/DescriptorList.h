/**
* @file DescriptorList.h.
* @brief The DescriptorList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Resource/BindGroup.h"
#include "Device/Graphics/Frontend/RHI/DescriptorList.h"

#include <map>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::WebGPU {

	/**
	* @brief WebGPU::DescriptorList Class.
	* This class defines the WebGPU::DescriptorList behaves.
	*/
	class DescriptorList : public ContextAccessor, public RHI::RHIDescriptorList::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit DescriptorList(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorList() override = default;

	public:

		/**
		* @brief Interface of Add ShaderConstant.
		*
		* @param[in] bytes bytes.
		*/
		void AddShaderConstant(uint32_t bytes) override;
		
		/**
		* @brief Interface of Add UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] bytes UniformBuffer bytes.
		*/
		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) override;

		/**
		* @brief Interface of Add Dynamic UniformBuffer.
		* 
		* @param[in] set .
		* @param[in] binding .
		* @param[in] bytes UniformBuffer bytes.
		*/
		void AddDynamicUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) override;
		
		/**
		* @brief Interface of Add UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void AddUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget) override;

		/**
		* @brief Interface of Add StorageTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void AddStorageTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget) override;
		
		/**
		* @brief Interface of Update UniformBuffer.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] data UniformBuffer data.
		*/
		void UpdateUniformBuffer(uint32_t set, uint32_t binding, const void* data) override;

		/**
		* @brief Interface of Update UniformTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget) override;

		/**
		* @brief Interface of Update StorageTexture.
		*
		* @param[in] set .
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateStorageTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget) override;
		
		/**
		* @brief Interface of Update DynamicUniformBufferOffset.
		*
		* @param[in] set .
		* @param[in] offset .
		*/
		void UpdateDynamicUniformBufferOffset(uint32_t set, uint32_t offset) override;
		
		/**
		* @brief Interface of Combine Shared DescriptorList.
		*
		* @param[in] shared RHIDescriptorList::Impl.
		*/
		void CombineSharedLayout(const RHI::RHIDescriptorList::Impl* shared) override;

		/**
		* @brief Interface of Build DescriptorList.
		*/
		void Build() override;

	public:
		
		/**
		* @brief Get WGPUBindGroupLayout.
		* 
		* @return Returns WGPUBindGroupLayout.
		*/
		const std::vector<WGPUBindGroupLayout>& GetLayouts() const { return m_BindGrouLayouts; }

		/**
		* @brief Get BindGroup.
		*
		* @return Returns BindGroup.
		*/
		const std::map<uint32_t, SP<Resource::BindGroup>>& GetGroups() const { return m_BindGroup; }
		
		/**
		* @brief Get ImmediateSize.
		*
		* @return Returns ImmediateSize.
		*/
		uint32_t GetImmediateSize() const { return m_ImmediateSize; }
		
	private:
		
		/**
		* @brief Access BindGroup, if not exist than create one.
		*
		* @param[in] set .
		* 
		* @return Returns BindGroup.
		*/
		SP<Resource::BindGroup> AccessSet(uint32_t set);
		
	private:
		
		std::map<uint32_t, SP<Resource::BindGroup>> m_BindGroup;             // @brief Container of BindGroup.
		std::vector<WGPUBindGroupLayout>            m_BindGrouLayouts;       // @brief Container of WGPUBindGroupLayout.
		uint32_t                                    m_ImmediateSize = 0;     // @brief ImmediateSize.
	};
}

#endif