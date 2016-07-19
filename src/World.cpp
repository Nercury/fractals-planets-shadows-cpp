#include "World.h"

#include "sdlgl.h"

static p<World> * wobj = NULL;

World::World()
{
}

World::~World()
{
}

void World::SetObjectCollision(WorldObject * obj, bool value)
{
	auto all_it = all_objects.find(obj);
	if (all_it == all_objects.end())
	{
		all_objects.insert(obj);
		if (value)
		{
			solid_objects.insert(obj);
		}
	}
	if (!value)
	{
		auto solid_it = solid_objects.find(obj);
		if (solid_it != solid_objects.end())
		{
			solid_objects.insert(obj);
		}
	}
}

void World::DeleteObject(WorldObject * obj)
{
	auto all_it = all_objects.find(obj);
	if (all_it != all_objects.end())
	{
		all_objects.erase(all_it);
	}
	auto solid_it = solid_objects.find(obj);
	if (solid_it != solid_objects.end())
	{
		solid_objects.erase(solid_it);
	}
}

void World::Render()
{
	for (auto it = all_objects.begin(); it != all_objects.end(); ++it)
	{
		(*it)->BeginScene();
	}
	for (auto it = all_objects.begin(); it != all_objects.end(); ++it)
	{
		wPushMatrix();
		(*it)->Render();
		wPopMatrix();
	}
	for (auto it = all_objects.begin(); it != all_objects.end(); ++it)
	{
		(*it)->EndScene();
	}
}

void World::RenderShadows(WorldObject * obj)
{
	if (obj->shadowObject)
	{
		obj->BeginScene();
		wPushMatrix();
		obj->Render();
		wPopMatrix();
		obj->EndScene();
	}
}

void World::RenderShadows()
{
	for (auto it = all_objects.begin(); it != all_objects.end(); ++it)
	{
		if ((*it)->shadowObject)
			(*it)->BeginScene();
	}
	for (auto it = all_objects.begin(); it != all_objects.end(); ++it)
	{
		if ((*it)->shadowObject)
		{
			wPushMatrix();
			(*it)->Render();
			wPopMatrix();
		}
	}
	for (auto it = all_objects.begin(); it != all_objects.end(); ++it)
	{
		if ((*it)->shadowObject)
			(*it)->EndScene();
	}
}

static void on_unused_world(World * w)
{
	delete wobj;
	wobj = NULL;
}

p<World> get_world()
{
	if (wobj == NULL)
	{
		p<World> * world = new p<World>(new World(), 1, boost::bind(&on_unused_world, _1));
		wobj = world;
		return *world;
	}
	else
	{
		return *wobj;
	}
}