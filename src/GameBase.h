#pragma once

#include "sdlgl.h"
#include "b_threading.h"

/*
This is base class which does some housekeeping common to all games:
hooks up events, assigns window with, height, and ratio and also does frame limiting
*/

class GameBase
{
private:
	boost::posix_time::time_duration normal_delta;
	void InternalResizeWindow(SDLGL* sdlgl);
	void InternalRender(SDLGL* sdlgl, boost::posix_time::time_duration delta);
protected:
	GLfloat ratio;
	GLint width;
	GLint height;
	virtual bool OnInitWindow(SDLGL* engine) = 0;
	virtual void OnResizeWindow(SDLGL* engine) = 0;
	virtual void OnRender(SDLGL* engine, boost::posix_time::time_duration delta) = 0;
	virtual void OnExitWindow(SDLGL* engine) = 0;
	virtual void OnKeyUp(SDLGL* engine, SDL_Event* ev) {};
	virtual void OnKeyDown(SDLGL* engine, SDL_Event* ev) {};
	virtual void OnMouseUp(SDLGL* engine, SDL_Event* ev) {};
	virtual void OnMouseDown(SDLGL* engine, SDL_Event* ev) {};
	virtual void OnMouseMove(SDLGL* engine, SDL_Event* ev) {};
public:
	GameBase(void);
	void Run(SDLGL & engine);
	virtual ~GameBase(void);
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Game";
		return ss.str();
	};
};
