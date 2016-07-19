#pragma once

#include <string>
#include <map>
#include <set>
#include "sdlgl.h"

class TextureInfo
{
public:
	std::set<GLuint*> links;
	GLuint textureID;
	int32_t width;
	int32_t height;
};

class TextureManager
{
private:
	std::map<std::string,TextureInfo*> files;
	bool modified;
public:
	TextureManager();
	virtual ~TextureManager(void);
	void MapFileTexture(GLuint & texture, std::string path);
	void MapFileTexture(GLuint & texture, std::string path, int32_t & width, int32_t & height);
	void RemoveTexture(std::string path, GLuint & texture);
	void WindowResize();
	void SceneStart();
};
