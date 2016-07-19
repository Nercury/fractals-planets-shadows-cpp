#pragma once

#include "ShaderParamBase.h"

class ParamUniform3f : public ShaderParamBase {
public:
	float v0,v1,v2;
	virtual void Apply(const char* name, GLenum program)
	{
		glUniform3fARB(glGetUniformLocationARB(program, name),v0,v1,v2);
	};
	ParamUniform3f(float v0, float v1, float v2)
		: v0(v0), v1(v1), v2(v2) {};
};

class ParamTexture : public ShaderParamBase {
public:
	int index;
	GLuint texture;
	virtual void Apply(const char* name, GLenum program)
	{
		glActiveTextureARB(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1iARB(glGetUniformLocationARB(program, name), index);
		glActiveTextureARB(0);
	};
	ParamTexture(int index, GLuint texture)
		: index(index), texture(texture) {};
};