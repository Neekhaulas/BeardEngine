#pragma once

#include "common.h"

bool Collision_AABB_Entity(entity* ent1, entity* ent2)
{
	if(ent1->position.x + ent1->size.x < ent2->position.x
		|| ent1->position.x > ent2->position.x + ent2->size.x
		|| ent1->position.y + ent1->size.y < ent2->position.x
		|| ent1->position.y > ent2->position.y + ent2->size.y)
		return false;
	return true;
}
