#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "object.h"
#include "entity.h"

#define GRAVITY -9.8f

void EnableGravity(Entity *player, float gravity);

#endif