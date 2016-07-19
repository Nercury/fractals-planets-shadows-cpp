#include "GameBase.h"

void GameBase::Run(SDLGL & engine)
{
	engine.InitFunction = boost::bind(&GameBase::OnInitWindow, this, _1);
	engine.ResizeFunction = boost::bind(&GameBase::InternalResizeWindow, this, _1);
	engine.RenderFunction = boost::bind(&GameBase::InternalRender, this, _1, _2);
	engine.ExitFunction = boost::bind(&GameBase::OnExitWindow, this, _1);
	engine.KeyUpFunction = boost::bind(&GameBase::OnKeyUp, this, _1, _2);
	engine.KeyDownFunction = boost::bind(&GameBase::OnKeyDown, this, _1, _2);
	engine.MouseUpFunction = boost::bind(&GameBase::OnMouseUp, this, _1, _2);
	engine.MouseDownFunction = boost::bind(&GameBase::OnMouseDown, this, _1, _2);
	engine.MouseMoveFunction = boost::bind(&GameBase::OnMouseMove, this, _1, _2);

	engine.Run(); // blocks
	
	engine.InitFunction.clear();
	engine.ResizeFunction.clear();
	engine.RenderFunction.clear();
	engine.ExitFunction.clear();
	engine.KeyUpFunction.clear();
	engine.KeyDownFunction.clear();
	engine.MouseUpFunction.clear();
	engine.MouseDownFunction.clear();
	engine.MouseMoveFunction.clear();
}

void GameBase::InternalResizeWindow(SDLGL* sdlgl)
{
	this->width = (GLsizei)sdlgl->GetWidth();
	this->height = (GLsizei)sdlgl->GetHeight();

	if ( height < width )
	{
		if ( height == 0 )
			height = 1;
		this->ratio = ( GLfloat )width / ( GLfloat )height;
	}

	OnResizeWindow(sdlgl);
}

void GameBase::InternalRender(SDLGL* sdlgl, boost::posix_time::time_duration render_delta)
{
	normal_delta += render_delta;
	
	if (normal_delta < boost::posix_time::milliseconds(10)) // frame limiting
	{
		ThreadSleep(5);
	}
	else
	{
		boost::posix_time::time_duration delta = normal_delta;
		normal_delta = boost::posix_time::seconds(0);

		OnRender(sdlgl, delta);
	}
}

GameBase::GameBase(void)
{
	normal_delta = boost::posix_time::milliseconds(0);
}

GameBase::~GameBase(void)
{
}
