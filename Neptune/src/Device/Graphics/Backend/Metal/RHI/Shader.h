/**
* @file Shader.h.
* @brief The Shader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Device/Graphics/Backend/Metal/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/Shader.h"

namespace Neptune::Metal {

	/**
	* @brief Metal::Shader Class.
	* This class defines the Metal::Shader behaves.
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

	private:
		
	};
}

#endif