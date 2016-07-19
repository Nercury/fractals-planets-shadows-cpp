#pragma once

#include <string>
#include <map>
#include <set>
#include "sdlgl.h"
#include "safep.hpp"

#define COMPILE_LOG_LENGTH 5120

class Shader;

class ShaderManager
{
private:
	char compileLog[COMPILE_LOG_LENGTH];
	std::map<std::string, GLenum> objects;
	std::set<Shader*> shaders;
public:
	ShaderManager();
	virtual ~ShaderManager(void);
	GLenum GetObject(std::string filename, GLenum type);
	bool LinkProgram(GLenum program);
	void WindowResize();
	bool ShaderRegistered(Shader * sh);
	void RegisterShader(Shader * sh);
	void UnregisterShader(Shader * sh);
	inline std::string toString() {
		std::ostringstream ss;
		ss << "ShaderManager";
		return ss.str();
	};
};