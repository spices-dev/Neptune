#include "Pchheader.h"
#include "Shader.h"
#include "Device/Graphics/Frontend/RHI/Shader.h"

namespace Neptune {
	
	void Shader::SetSource(const std::filesystem::path& path)
	{
		std::vector<uint8_t> spirv = Compile(path.generic_string());

		m_RHIResource = CreateSP<RHI::Shader>();
		m_RHIResource->SetSource(spirv);
		m_RHIResource->SetName(m_Name);
	}

	std::vector<uint8_t> Shader::Compile(const std::string& path)
	{
		std::ifstream file(NEPTUNE_ASSETS_PATH + path, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			std::stringstream ss;
			ss << "Failed to open file: " << path;
			
			NEPTUNE_CORE_ERROR(ss.str())
			
			return {};
		}
		
		auto size = file.tellg();
		
		std::vector<uint8_t> buffer(size);
		
		file.seekg(0);
		
		file.read(reinterpret_cast<char*>(buffer.data()), size);
		
		file.close();
		
		return buffer;
	}

}