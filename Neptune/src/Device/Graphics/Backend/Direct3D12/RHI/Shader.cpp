/**
* @file Shader.cpp.
* @brief The Shader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Shader.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Direct3D12 {

	void Shader::SetSource(const std::vector<uint8_t>& source)
	{
		NEPTUNE_PROFILE_ZONE

		m_Shader.CreateBlob(source.data(), source.size());
	}

	void Shader::SetName(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Shader, name)
	}
}

#endif