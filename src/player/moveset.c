#include "moveset.h"

extern float dx;
extern bool pause;

static Vector3 dislocation = {0};

void movesetMouse(Camera3D *camera, Mouse *mouse){
    static unsigned char status = SUSPEND;

    if (IsKeyPressed(KEY_ESCAPE)){
        if (mouse->screen_status == LOCK){
            mouse->screen_status = OUT_SCREEN;
            pause = 1;
        }
        else if (mouse->screen_status == SUSPEND){
            mouse->screen_status = IN_SCREEN;
            pause = 0;
        }
    }

    switch (mouse->screen_status){
        case IN_SCREEN: DisableCursor();
                        mouse->screen_status = LOCK;
                        break;

        case OUT_SCREEN:EnableCursor();
                        mouse->screen_status = SUSPEND;
                        break;

        case LOCK:      movesetCamera(camera, mouse);
                        break;

        case SUSPEND:   break;
    }
}

void movesetCamera(Camera3D *camera, Mouse *mouse){
    Vector2 mouse_delta = GetMouseDelta();
    
    mouse->yaw += mouse_delta.x * mouse->sensi;
    mouse->pitch -= mouse_delta.y * mouse->sensi;
    
    if (mouse->pitch > 89.0f)  mouse->pitch = 89.0f;
    if (mouse->pitch < -89.0f) mouse->pitch = -89.0f;
    
    dislocation.x = cos(toradians(mouse->yaw)) * cos(toradians(mouse->pitch));
    dislocation.y = sin(toradians(mouse->pitch));
    dislocation.z = sin(toradians(mouse->yaw)) * cos(toradians(mouse->pitch));
    
    camera->target = Vector3Sum(camera->position, _Vector3Normalize(dislocation));
    
    return;
}

void movesetPlayer(Camera3D *camera, Entity *player){
    
    // KEY_P & KEY_O debug keys
    if (IsKeyDown(KEY_P)){
        player->pos.y++;
        player->body.position = player->pos;
    }

    if (IsKeyDown(KEY_O)){
        player->pos.y--;
        player->body.position = player->pos;
    }

    if (IsKeyDown(KEY_W)){
        Vector3 front_vector = dislocation;

        player->pos = Vector3Sum(player->pos, (Vector3){(front_vector.x * player->vel), 0.0f, (front_vector.z * player->vel)});
        player->body.position = player->pos;
    }
    
    if (IsKeyDown(KEY_S)){
        player->pos = _Vector3Subtract(player->pos, (Vector3){(dislocation.x * player->vel), 0.0f, (dislocation.z * player->vel)});
        player->body.position = player->pos;
    }

    if (IsKeyDown(KEY_A)){
        Vector3 side_vector = _Vector3Normalize(Vector3Cross(dislocation, camera->up));

        player->pos = _Vector3Subtract(player->pos, (Vector3){(side_vector.x * player->vel), (side_vector.y * player->vel), (side_vector.z * player->vel)});
        player->body.position = player->pos;
    }

    if (IsKeyDown(KEY_D)){
        Vector3 side_vector = _Vector3Normalize(Vector3Cross(dislocation, camera->up));

        player->pos = Vector3Sum(player->pos, (Vector3){(side_vector.x * player->vel), (side_vector.y * player->vel), (side_vector.z * player->vel)});
        player->body.position = player->pos;
    }
}

void UpdatePos(Camera3D *cam, Entity *player, Object *object){
    bool collision = CheckCollision(&player->body, object);
    Two_Sides result = aabbCollision(&player->body, object);
    
    if (CheckPlayerCollision(&player->body, object)){
        player->onGround = 1;
        player->pos.y = player->pos.y + (result.sides_2.max.y - result.sides_1.min.y) + 0.001f;

        player->body.position = player->pos;
        cam->position = player->pos;
    }
    
    else if (!collision) {
        player->body.position = player->pos; 
        cam->position = player->pos;
    }

}

void EnableJump(Entity *player){
    static double accel = 0.0f;

    if (IsKeyPressed(KEY_SPACE) && player->onGround){
        player->onGround = 0;
        accel = 1.0f;
        player->velY = accel;
    }

    if (!player->onGround)
        player->pos.y += player->velY * dx;
    
    else accel = 0.0f;
}