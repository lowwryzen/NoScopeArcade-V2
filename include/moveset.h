#ifndef MOVESET_H
#define MOVESET_H

#include <math.h>

#include "raylib.h"

#include "vector.h"
#include "world.h"
#include "object.h"
#include "entity.h"

#define toradians(x) (x * (PI/180.0f))

typedef enum{
    OUT_SCREEN = 0,
    IN_SCREEN  = 1,
    SUSPEND    = 2,
    LOCK       = 4
} Screen_Status;

typedef struct {
    Screen_Status screen_status;
    float sensi;
} Mouse;

void movesetMouse(Camera3D *camera, Mouse *mouse);
void movesetCamera(Camera3D *camera, float sensi);
void movesetPlayer(Camera3D *camera, Entity *player);

void UpdatePos(Camera3D *cam, Entity *player, Object *object);

void EnableJump(Entity *player);
#endif