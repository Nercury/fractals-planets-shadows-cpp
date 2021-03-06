#pragma once

#include <string>
#include <map>
#include "sdlgl.h"
#include "ShaderManager.h"
#include "safep.hpp"

#include "ShaderParamBase.h"
#include "ShaderParams.h"

class Shader
{
private:
	p<ShaderManager> manager;
	std::string vfile;
	std::string ffile;
	GLHANDLE vs;
	GLHANDLE ps;
	GLHANDLE program;
	std::map<std::string, std::shared_ptr<ShaderParamBase>> params;
	void LoadShader();
public:
	bool enabled;
	Shader(p<ShaderManager> manager, std::string vertexfile, std::string fragfile);
	virtual ~Shader(void);
	void Use();
	int Uniform(std::string name) { return glGetUniformLocationARB(program, name.c_str()); };
	int Attr(std::string name) { return glGetUniformLocationARB(program, name.c_str()); };
	void BindTexture(std::string name, int index, GLuint texture) 
	{
		SetParam(name, std::make_shared<ParamTexture>(index, texture));
	};
	inline bool IsValid() { return program != 0; };
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Shader vs:" << vfile << " ps:" << ffile;
		return ss.str();
	};
	/*void glUniform{1|2|3|4}{f|i}ARB(GLint location, TYPE val)
	void glUniform{1|2|3|4}{f|i}vARB(GLint location, GLuint count, const TYPE * vals)
	void glUniformMatrix{2|3|4|}fvARB(GLint location, GLuint count, GLboolean transpose, const GLfloat * vals)*/
	inline void SetParam(std::string name, std::shared_ptr<ShaderParamBase> param)
	{
		auto it = params.find(name);
		if (it == params.end())
		{
			params.insert({name, param});
		}
		else
		{
            it->second = param;
		}
	};
	inline void BindParameters()
	{
		for (auto it = params.begin(); it != params.end(); ++it)
		{
			it->second->Apply(it->first.c_str(), program);
		}
	};
	void Uniform3f(std::string name, float v0, float v1, float v2) { SetParam(name, std::make_shared<ParamUniform3f>(v0, v1, v2)); };
	void Reset();
	void Rebuild();
};