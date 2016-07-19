#pragma once

#include "sdlgl.h"

class ShaderParamBase
{
public:
	virtual void Apply(const char* name, GLenum program) {};
	ShaderParamBase() {};
};