/**
* @file VertexBuffer.h.
* @brief The VertexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Device/Graphics/Backend/Metal/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/VertexBuffer.h"

namespace Neptune::Metal {

	/**
	* @brief Metal::VertexBuffer Class.
	* This class defines the Metal::VertexBuffer behaves.
	*/
	class VertexBuffer : public ContextAccessor, public RHI::RHIVertexBuffer::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit VertexBuffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~VertexBuffer() override = default;

	private:
		
	};
}

#endif