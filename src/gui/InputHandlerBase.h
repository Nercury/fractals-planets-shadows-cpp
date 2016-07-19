#pragma once

#include <SDL.h>

class InputHandlerBase
{
public:
	InputHandlerBase() {};
	virtual ~InputHandlerBase() {};
	virtual bool OnKeyUp(SDL_Event* ev) { return false; };
	virtual bool OnKeyDown(SDL_Event* ev) { return false; };
	virtual bool OnMouseUp(SDL_Event* ev, int32_t x, int32_t y) { return false; };
	virtual bool OnMouseDown(SDL_Event* ev, int32_t x, int32_t y) { return false; };
	virtual bool OnMouseMove(SDL_Event* ev, int32_t x, int32_t y) { return false; };
};