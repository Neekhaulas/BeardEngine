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

bool Collision_AABB_Entity_Offset(entity* ent1, entity* ent2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float left = ent2->position.x - (ent1->position.x + ent1->size.x);
	float right = (ent2->position.x + ent2->size.x) - ent1->position.x;
	float top = ent2->position.y - (ent1->position.y + ent1->size.y);
	float bottom = (ent2->position.y + ent2->size.y) - ent1->position.y;

	if(left > 0 || right < 0 || top > 0 || bottom < 0)
	{
		return false;
	}

	moveX = abs(left) < right ? left : right;
	moveY = abs(top) < bottom ? top : bottom;

	if (abs(moveX) < abs(moveY))
	{
		moveY = 0.0f;
	}
	else
	{
		moveX = 0.0f;
	}

	return true;
}