/**
* @file Shader.cpp.
* @brief The Shader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Shader.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"

namespace Neptune::WebGPU {

	void Shader::SetSource(const std::vector<uint8_t>& source)
	{
		NEPTUNE_PROFILE_ZONE

		WGPUShaderModuleDescriptor desc{};

		m_Shader.CreateShaderModule(GetContext().Get<IDevice>()->Handle(), desc);
	}

	void Shader::SetName(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Shader,name)
	}
}

#endif