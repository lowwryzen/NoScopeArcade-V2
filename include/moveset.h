#ifndef MOVESET_H
#define MOVESET_H

#include "raylib.h"

#define toradians(x) (x * (PI/180.0f))

typedef enum{
    OUT_SCREEN = 0,
    IN_SCREEN  = 1,
    SUSPEND    = 2,
    LOCK       = 4
} Screen_Status;

void movesetMouse(Camera3D *mouse);
void movesetCamera(Camera3D *camera);
void movesetPlayer(Camera3D *camera, Entity *player);

void UpdatePos(Camera3D *cam, Entity *player, Object *object);

void EnableJump(Entity *player);
#endif