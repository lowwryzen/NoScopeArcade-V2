#include "world.h"

extern float dx;

void EnableGravity(Entity *player, float gravity){
    static double accel = 0.0;

    if (!player->onGround){
        player->velY+= accel * dx;
        player->pos.y+= player->velY * dx;
        accel+= gravity * dx;
    }
    else {
        player->velY = 0.0f;
        accel = 0.0f;
    }
}