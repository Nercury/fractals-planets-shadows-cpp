#pragma once

#include <string>
#include <map>
#include <set>
#include "sdlgl.h"
#include "safep.hpp"

#define COMPILE_LOG_LENGTH 5120

class Shader;

#ifdef __APPLE__
#define GLHANDLE GLhandleARB
#else
#define GLHANDLE GLenum
#endif

class ShaderManager
{
private:
	char compileLog[COMPILE_LOG_LENGTH];
	std::map<std::string, GLHANDLE> objects;
	std::set<Shader*> shaders;
public:
	ShaderManager();
	virtual ~ShaderManager(void);
    GLHANDLE GetObject(std::string filename, GLenum type);
	bool LinkProgram(GLHANDLE program);
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