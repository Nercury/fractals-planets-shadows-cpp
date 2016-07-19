#pragma once

#include "sdlgl.h"
#include "safep.hpp"
#include "TextureManager.h"
#include <sstream>
#include <string>

class Texture
{
private:
	GLuint texture;
	std::string path;
	p<TextureManager> manager;
	int32_t width;
	int32_t height;
	bool bind_on_render;
public:
	Texture(p<TextureManager> manager, std::string path);
	virtual ~Texture(void);
	void Render(GLint w, GLint h);
	void Render(GLfloat w, GLfloat h);
	void RenderPart(GLint sx, GLint sy, GLint w, GLint h);
	void RenderPartScaled(GLint sx, GLint sy, GLint sw, GLint sh, GLint w, GLint h);
	void RenderPartScaledWithBorder(GLint sx, GLint sy, GLint sw, GLint sh, GLint w, GLint h, GLint bl, GLint bt, GLint br, GLint bb);
	inline void SetBindOnRender(bool value) { bind_on_render = value; };
	inline std::string Path() { return path; };
	inline int32_t Width() { return width; };
	inline int32_t Height() { return height; };
	inline GLuint Get() { return texture; };
	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Texture:" << this->path;
		return ss.str();
	};
};