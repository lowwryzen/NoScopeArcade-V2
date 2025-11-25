#include "raylib.h"
#include "object.h"
#include "entity.h"

void EnableGravity(Entity *player, float gravity){
    static double accel = 0.0f;

    if (!player->onGround){
        player->pos.y+= gravity * accel;
        accel+=0.001f;
    }
    else accel = 0.0f;
}