#pragma once

#include "Window.h"
#include "../Texture.h"
#include "../glst/GLST_Text.h"

class DecoratedWindow
	: public MWindow
{
private:
	p<Texture> texture;
	GLST_Text * title_text;
	bool overButton;
	bool downButton;
	bool down;
	bool downResize;
public:
	DecoratedWindow(void);
	virtual ~DecoratedWindow(void);
	virtual void Initialize();
	virtual void Terminate();
	virtual void Render(boost::posix_time::time_duration delta);
	virtual bool OnMouseUp(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseDown(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseMove(SDL_Event* ev, int32_t x, int32_t y);
};