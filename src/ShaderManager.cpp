#include "ShaderManager.h"

#include "Shader.h"

#include <sstream>

using namespace std;

ShaderManager::ShaderManager(void)
{

}

ShaderManager::~ShaderManager(void)
{
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		(*it)->Reset();
	}
	shaders.clear();
}

bool ShaderManager::LinkProgram(GLHANDLE program)
{
	cout << "Linking shader..." << endl;
	glLinkProgramARB(program);
	int32_t char_count = 0;
	glGetInfoLogARB(program, COMPILE_LOG_LENGTH, &char_count, &compileLog[0]);
	int result;
	glGetProgramiv((size_t)program, GL_LINK_STATUS, &result);
	if (char_count > 0)
	{
		string s(compileLog, char_count);
		cout << s << endl;
	}
	if (result != GL_TRUE)
	{
		cout << "Failed to link shader." << endl << endl;
		return false;
	}
	cout << "Shader linked successfully." << endl;
	return true;
}

GLHANDLE ShaderManager::GetObject(string filename, GLenum type)
{
	auto it = objects.find(filename);
	if (it != objects.end())
	{
		return it->second;
	}
	else
	{
		cout << "Loading shader from " << filename << "..." << endl;

		stringstream ss;
		std::string line;
		std::ifstream in(filename);

		if (in.good())
		{
			while (std::getline(in, line))
				ss << line << "\n";
		}
		else
		{
			std::cout << "Failed to read file: " << filename << endl;
			return NULL;
		}

        GLHANDLE shader = glCreateShaderObjectARB(type);

		//cout << "Loading shader source..." << endl;
		string sourcestring = ss.str();
		const char * source = sourcestring.c_str();
		glShaderSourceARB(shader, 1, &source, NULL);
		//cout << "Source assigned:\n" << source << endl;

		cout << "Compiling shader..." << endl;
		glCompileShaderARB(shader);
		int32_t char_count = 0;
		glGetInfoLogARB(shader, COMPILE_LOG_LENGTH, &char_count, &compileLog[0]);
		int result;
		glGetShaderiv((size_t)shader, GL_COMPILE_STATUS, &result);
		if (char_count > 0)
		{
			string s(compileLog, char_count);
			cout << s << endl;
		}
		if (result != GL_TRUE)
		{
			cout << "Failed to compile shader." << endl << endl;
			glDeleteObjectARB(shader);
			return NULL;
		}
		cout << "Shader compiled successfully." << endl;

		objects.insert(pair<string, GLHANDLE>(filename, shader));

		return shader;
	}
}

void ShaderManager::WindowResize()
{
	cout << "Deleting shader program objects..." << endl;
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		glDeleteObjectARB(it->second);
	}
	objects.clear();
	set<Shader*> tmp;
	cout << "Deleting shader objects..." << endl;
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		(*it)->Reset();
		tmp.insert(*it);
	}
	shaders.clear();
	cout << "Rebuilding shaders..." << endl;
	for (auto it = tmp.begin(); it != tmp.end(); ++it)
	{
		(*it)->Rebuild();
	}
}

bool ShaderManager::ShaderRegistered(Shader * sh)
{
	return shaders.find(sh) != shaders.end();
}

void ShaderManager::RegisterShader(Shader * sh)
{
	auto it = shaders.find(sh);
	if (it == shaders.end())
	{
		shaders.insert(sh);
	}
}


void ShaderManager::UnregisterShader(Shader * sh)
{
	auto it = shaders.find(sh);
	if (it == shaders.end())
	{
		shaders.erase(it);
	}
}
