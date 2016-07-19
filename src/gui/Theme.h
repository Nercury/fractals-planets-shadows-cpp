#pragma once

#include "glgui.h"
#include "../TextureManager.h"
#include "../safep.hpp"
#include "../types.h"
#include <string>

#include <map>

#include "../Texture.h"

class Theme
{
private:
	p<TextureManager> manager;
	std::map<std::string, p<Texture>> textures;
	void OnUnusedDeco(Texture * texture);
public:
	Theme();
	virtual ~Theme() {};
	p<Texture> GetTexture(std::string name);
	inline void WindowResize() { manager.o()->WindowResize(); };
	inline void SceneStart() { manager.o()->SceneStart(); };
};