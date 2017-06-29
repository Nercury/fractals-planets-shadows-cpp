#include "Shader.h"

using namespace std;

Shader::Shader(p<ShaderManager> manager, std::string vertexfile, std::string fragfile)
	: manager(manager), vfile(vertexfile), ffile(fragfile), vs(0), ps(0), program(0)
{
	enabled = true;
	manager.o()->RegisterShader(this);
}

Shader::~Shader(void)
{
	if (!manager.empty())
	{
		if (manager.o()->ShaderRegistered(this))
		{
			Reset();
			manager.o()->UnregisterShader(this);
		}
	}
}

void Shader::LoadShader()
{
	vs = manager.o()->GetObject(vfile, GL_VERTEX_SHADER_ARB);
	ps = manager.o()->GetObject(ffile, GL_FRAGMENT_SHADER_ARB);
	GLHANDLE program = glCreateProgramObjectARB();
	if (vs != NULL)
		glAttachObjectARB(program, vs);
	if (ps != NULL)
		glAttachObjectARB(program, ps);
	if (vs != NULL && ps != NULL)
	{
		if (manager.o()->LinkProgram(program))
			this->program = program;
		else
			glDeleteObjectARB(program);
	}
	else
	{
		glDeleteObjectARB(program);
	}
	manager.o()->RegisterShader(this);
}

void Shader::Use()
{
	if (program != 0)
		glUseProgramObjectARB(program);
	BindParameters();
}

void Shader::Reset()
{
	glDeleteObjectARB(program);
}

void Shader::Rebuild()
{
	LoadShader();
}