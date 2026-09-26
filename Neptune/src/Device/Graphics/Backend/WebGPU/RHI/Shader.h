/**
* @file Shader.h.
* @brief The Shader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/ShaderModule.h"
#include "Device/Graphics/Frontend/RHI/Shader.h"

namespace Neptune::WebGPU {

	/**
	* @brief WebGPU::Shader Class.
	* This class defines the WebGPU::Shader behaves.
	*/
	class Shader : public ContextAccessor, public RHI::RHIShader::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Shader(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Shader() override = default;

	public:

		/**
		* @brief Interface of Set Shader Source.
		*
		* @param[in] source Shader Source.
		*/
		void SetSource(const std::vector<uint8_t>& source) override;

		/**
		* @brief Interface of Set Shader Name.
		*
		* @param[in] name Shader Name.
		*/
		void SetName(const std::string& name) override;

	public:

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::ShaderModule::Handle& Handle() const { return m_Shader.GetHandle(); }

	private:

		Unit::ShaderModule m_Shader;          // @brief This Shader.
	};
}

#endif