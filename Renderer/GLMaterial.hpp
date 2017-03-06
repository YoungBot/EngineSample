//==========================================================
//GLMaterial.hpp
//==========================================================

#pragma once
#include "GLShader.hpp"

struct GLSampler
{
	GLSampler()
	{
		//m_samplerID = CreateSampler(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
		gTexDiffuse =nullptr;
		gTexNormal = nullptr;
		gTexSpecular = nullptr;
		gTexEmissive = nullptr;
		gTexSpecGlossEmit = nullptr;
	}
	GLuint CreateSampler(GLenum min_filter, GLenum mag_filter, GLenum u_wrap, GLenum v_wrap)
	{
		GLuint sampler_id;
		glGenSamplers(1, &sampler_id);
		if (NULL == sampler_id) {
			return NULL;
		}
		glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, min_filter);			// Default: GL_NEAREST_MIPMAP_LINEAR
		glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, mag_filter);			// Default: GL_LINEAR
		glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, u_wrap);					// Default: GL_REPEAT
		glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, v_wrap);					// Default: GL_REPEAT
		m_samplerID = sampler_id;
		return sampler_id;
	}
	GLuint m_samplerID;
	Texture* gTexDiffuse;
	Texture* gTexNormal;
	Texture* gTexSpecular;
	Texture* gTexEmissive;
	Texture* gTexSpecGlossEmit;
};

class GLMaterial
{
public:
	GLMaterial();
	GLMaterial(GLShader m_program, GLSampler m_sampler);


	GLShader m_program;
	GLSampler m_sampler;
};

