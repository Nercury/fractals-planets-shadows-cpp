#pragma once

#include "GameBase.h"

/* c class which extends GameBase class */
class Example :	public GameBase
{
private: // put any variables which are internal to this game here
	double rotation;

protected: // copy pasted these methods (they are called when something interesting happens)
	virtual bool OnInitWindow(SDLGL* engine);
	virtual void OnResizeWindow(SDLGL* engine);
	virtual void OnRender(SDLGL* engine, boost::posix_time::time_duration delta);
	virtual void OnExitWindow(SDLGL* engine);
	virtual void OnKeyDown(SDLGL* engine, SDL_Event* ev);

public: // public functions visible from outside
	Example(void);
	virtual ~Example(void);
};
