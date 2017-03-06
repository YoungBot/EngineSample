//==========================================================
//GLMaterial.cpp
//==========================================================

#include "GLMaterial.hpp"

GLMaterial::GLMaterial()
{
	m_program = GLShader("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
	m_sampler.CreateSampler(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
	m_sampler.gTexDiffuse = Texture::CreateOrGetTexture("Data/Images/white.png");//testNormalMap
}

GLMaterial::GLMaterial(GLShader program, GLSampler sampler)
{
	m_program = program;
	m_sampler = sampler;
}