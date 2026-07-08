#include "Pchheader.h"
#include "Shader.h"
#include "Device/Graphics/Frontend/RHI/Shader.h"

namespace Neptune {
	
	void Shader::SetSource(const std::filesystem::path& path)
	{
		std::vector<uint8_t> spirv = Compile(path.string());

		m_RHIResource = CreateSP<RHI::Shader>();
		m_RHIResource->SetSource(spirv);
		m_RHIResource->SetName(m_Name);
	}

	std::vector<uint8_t> Shader::Compile(const std::string& data)
	{
		return {};
	}

}