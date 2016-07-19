#include "Collision.h"

#include "World.h"
#include "WorldObject.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

void Collision::OnAssign(WorldObject * current)
{
	get_world().o()->SetObjectCollision(current, false);
}