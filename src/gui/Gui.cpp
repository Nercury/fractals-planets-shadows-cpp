#include "Gui.h"

#include "GuiLayer.h"
#include "DecoratedWindow.h"
#include "../L.h"

Gui::Gui()
	: width(400), height(300), activeLayerIndex(-1), mouseLayerIndex(-1), mouseOverLayerIndex(-1)
{
	for (int i = 0; i < 3; i++)
		layers[i] = new GuiLayer(this, boost::bind(&Gui::OnLayerActivate, this, i), 
		boost::bind(&Gui::OnLayerDeactivate, this, i), 
		boost::bind(&Gui::OnLayerMouseGrab, this, i), 
		boost::bind(&Gui::OnLayerMouseUngrab, this, i), 400, 300);
}

Gui::Gui(int32_t width, int32_t height)
	: width(width), height(height), activeLayerIndex(-1), mouseLayerIndex(-1), mouseOverLayerIndex(-1)
{
	for (int i = 0; i < 3; i++)
		layers[i] = new GuiLayer(this, boost::bind(&Gui::OnLayerActivate, this, i), 
		boost::bind(&Gui::OnLayerDeactivate, this, i),
		boost::bind(&Gui::OnLayerMouseGrab, this, i), 
		boost::bind(&Gui::OnLayerMouseUngrab, this, i), width, height);
}

Gui::~Gui()
{
	for (int i = 0; i < 3; i++)
		delete layers[i];
}

GuiLayer * Gui::layerTop(void)
{
	return layers[2];
}

GuiLayer * Gui::layer(void)
{
	return layers[1];
}

GuiLayer * Gui::layerBack(void)
{
	return layers[0];
}

void Gui::SetSize(int32_t width, int32_t height)
{
	for (int i = 0; i < 3; i++)
		layers[i]->SetSize(width, height);
	theme->WindowResize();
}

void Gui::Render(boost::posix_time::time_duration delta)
{
	theme->SceneStart();
	for (int i = 0; i < 3; i++)
		layers[i]->Render(delta);
}

void Gui::OnLayerMouseGrab(int layerIndex)
{
	//l("On layer mouse grab: ", layerIndex, L_INFO);
	if (layerIndex >= 0 && layerIndex < 3)
	{
		if (mouseLayerIndex != -1)
		{
			layers[mouseLayerIndex]->UngrabMouse();
		}
		mouseLayerIndex = layerIndex;
	}
}

void Gui::OnLayerMouseUngrab(int layerIndex)
{
	//l("On layer mouse ungrab: ", layerIndex, L_INFO);
	mouseLayerIndex = -1;
}

void Gui::OnLayerActivate(int layerIndex)
{
	//l("On layer activate: ", layerIndex, L_INFO);
	if (layerIndex >= 0 && layerIndex < 3 && layerIndex != activeLayerIndex)
	{
		activeLayerIndex = layerIndex;
		for (int i = 0; i < 3; i++)
			if (i != layerIndex)
				layers[i]->Deactivate();
			else
				layers[i]->Activate();
	}
}

void Gui::OnLayerDeactivate(int layerIndex)
{
	//l("On layer deactivate: ", layerIndex, L_INFO);
	if (layerIndex >= 0 && layerIndex < 3 && layerIndex != activeLayerIndex)
	{
		activeLayerIndex = -1;
		for (int i = 2; i >= 0; i--)
			if (layers[i]->HasWindows() && activeLayerIndex == -1)
			{
				layers[i]->Activate();
				activeLayerIndex = i;
			}
			else
			{
				layers[i]->Deactivate();
			}
	}
}

bool Gui::OnKeyUp(SDL_Event* ev)
{
	//l("Key up", L_INFO);
	if (activeLayerIndex != -1)
		return layers[activeLayerIndex]->OnKeyUp(ev);
	return false;
}

bool Gui::OnKeyDown(SDL_Event* ev)
{
	//l("Key down", L_INFO);
	if (activeLayerIndex != -1)
		return layers[activeLayerIndex]->OnKeyDown(ev);
	return false;
}

bool Gui::OnMouseUp(SDL_Event* ev)
{
	//l("Mouse up", L_INFO);
	if (mouseLayerIndex != -1)
	{
		layers[mouseLayerIndex]->OnMouseUp(ev);
		return true;
	}
	else
	{
		for (int i = 2; i >= 0; i--)
			if (layers[i]->OnMouseUp(ev))
				return true;
	}
	return false;
}

bool Gui::OnMouseDown(SDL_Event* ev)
{
	//l("Mouse down", L_INFO);
	for (int i = 2; i >= 0; i--)
		if (layers[i]->OnMouseDown(ev))
			return true;
	return false;
}

bool Gui::OnMouseMove(SDL_Event* ev)
{
	bool moveResult = false;
	if (mouseLayerIndex != -1)
	{
		layers[mouseLayerIndex]->OnMouseMove(ev);
		moveResult = true;
	}
	else
	{
		for (int i = 2; i >= 0; i--)
			if (layers[i]->OnMouseMove(ev))
			{
				moveResult = true;
				break;
			}
	}
	return moveResult;
}