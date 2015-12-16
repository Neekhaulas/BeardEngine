#include "common.h"

void Entity_Update(dynamic_entity *ent, int delta)
{
	if (!ent->applyGravity)
		return;

	ent->velocity.y += Cvar_GetFloat("g_gravity") * ((float)delta / 1000.0f);
	Clamp(ent->velocity.y, -100.f, 10.f);
}

void Entity_Resolve_Collision(dynamic_entity *ent1, entity *ent2)
{
	/*float x, y;

	if (Collision_AABB_Entity_Offset(ent1, ent2, x, y))
	{
		if (x != 0)
		{
			ent1->velocity.x = 0;
			ent1->position.x += x;
		}
		
		if (y != 0)
		{
			ent1->velocity.y = 0;
			ent1->position.y += y;
		}
	}*/

	ent1->position.x += ent1->velocity.x;
	ent1->position.y += ent1->velocity.y;
}