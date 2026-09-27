/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Pipeline.h"
#include "Device/Graphics/Backend/OpenGL/RHI/Shader.h"
#include "Device/Graphics/Backend/OpenGL/RHI/RenderPass.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/OpenGL/Converter.h"

namespace Neptune::OpenGL {

	void Pipeline::SetDefault()
	{
		NEPTUNE_PROFILE_ZONE

		m_VAO         = 0;
		m_Topology    = GL_TRIANGLES;
		m_CullMode    = GL_BACK;

		m_Shaders.clear();
	}

	void Pipeline::SetRenderPass(const SP<RHI::RenderPass>& renderPass)
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass = renderPass->GetRHIImpl<RenderPass>();
	}

	void Pipeline::SetVertexAttributeLayout()
	{

	}

	void Pipeline::SetDescriptorList(const SP<RHI::DescriptorList>& descriptorList)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void Pipeline::SetCullMode(ECullMode mode)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CullMode = ToGLCullMode(mode);
	}

	void Pipeline::SetTopology(ETopology topology)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Topology = ToGLTopology(topology);
	}
	
	void Pipeline::AddShader(ShaderStage stage, const SP<RHI::Shader>& shader)
	{
		NEPTUNE_PROFILE_ZONE

		m_Shaders.emplace_back(shader->GetRHIImpl<Shader>()->Handle());
	}

	void Pipeline::BuildGraphicPipeline()
	{
		NEPTUNE_PROFILE_ZONE

		m_Pipeline.CreateProgram();

		std::ranges::for_each(m_Shaders, [&](const auto& shader){ glAttachShader(m_Pipeline.GetHandle(), shader); });

		glLinkProgram(m_Pipeline.GetHandle());

		GLint status = GL_FALSE;
		
		glGetProgramiv(m_Pipeline.GetHandle(), GL_LINK_STATUS, &status);
		
		if (status != GL_TRUE)
		{
			GLint length = 0;
			
			glGetProgramiv(m_Pipeline.GetHandle(), GL_INFO_LOG_LENGTH, &length);

			std::string log(length, '\0');
			
			glGetProgramInfoLog(m_Pipeline.GetHandle(), length, nullptr, log.data());

			NEPTUNE_LOG_CORE(E) << "GraphicPipeline Link Failed: " << log;
		}

		std::ranges::for_each(m_Shaders, [&](const auto& shader){ glDetachShader(m_Pipeline.GetHandle(), shader); });
		
		DEBUGUTILS_SETOBJECTNAME(m_Pipeline, "GraphicPipeline")
	}
	
	void Pipeline::BuildComputePipeline()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Pipeline.CreateProgram();
		
		glAttachShader(m_Pipeline.GetHandle(), m_Shaders[0]);
		
		glLinkProgram(m_Pipeline.GetHandle());

		GLint status = GL_FALSE;
		
		glGetProgramiv(m_Pipeline.GetHandle(), GL_LINK_STATUS, &status);
		
		if (status != GL_TRUE)
		{
			GLint length = 0;
			
			glGetProgramiv(m_Pipeline.GetHandle(), GL_INFO_LOG_LENGTH, &length);

			std::string log(length, '\0');
			
			glGetProgramInfoLog(m_Pipeline.GetHandle(), length, nullptr, log.data());

			NEPTUNE_LOG_CORE(E) << "ComputePipeline Link Failed: " << log;
		}

		glDetachShader(m_Pipeline.GetHandle(), m_Shaders[0]);

		DEBUGUTILS_SETOBJECTNAME(m_Pipeline, "ComputePipeline")
	}

	void Pipeline::BindPipeline() const
	{
		NEPTUNE_PROFILE_ZONE
		
		glUseProgram(m_Pipeline.GetHandle());
		
		glBindVertexArray(m_VAO);

		if (m_CullMode != GL_NONE)
		{
			glEnable(GL_CULL_FACE);
			
			glCullFace(m_CullMode);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}
}

#endif