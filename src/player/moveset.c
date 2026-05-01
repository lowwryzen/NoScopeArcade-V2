#include "moveset.h"

static float yaw = 0.0f;
static float pitch = 0.0f;

static float sensi = 0.1f; // Temp var

static Vector3 dislocation = {0};

void movesetMouse(Camera3D *mouse){
    static unsigned char status = SUSPEND;

    if (IsKeyPressed(KEY_TAB)){
        if (status == LOCK){
            status = OUT_SCREEN;
        }
        else if (status == SUSPEND){
            status = IN_SCREEN;
        }
    }

    switch (status){

    case IN_SCREEN: DisableCursor();
                    status = LOCK;
                    break;

    case OUT_SCREEN:EnableCursor();
                    status = SUSPEND;
                    break;

    case LOCK:      movesetCamera(mouse);
                    break;

    case SUSPEND:   break;
    }
}

void movesetCamera(Camera3D *camera){
    Vector2 mouse_delta = GetMouseDelta();
    
    yaw += mouse_delta.x * sensi;
    pitch -= mouse_delta.y * sensi;
    
    if (pitch > 89.0f){pitch = 89.0f;}
    if (pitch < -89.0f){pitch = -89.0f;}
    
    dislocation.x = cos(toradians(yaw)) * cos(toradians(pitch));
    dislocation.y = sin(toradians(pitch));
    dislocation.z = sin(toradians(yaw)) * cos(toradians(pitch));
    
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
    
    if (CheckPlayerCollision(&player->body, object) && result.sides_1.min.y == result.sides_2.max.y + 0.001f){
        player->onGround = 1;
        player->pos.y = player->pos.y + (result.sides_2.max.y - result.sides_1.min.y) + 0.001f;

        player->body.position = player->pos;
        cam->position = player->pos;
    }
    
    else if (!collision) {
        player->body.position = player->pos; 
        cam->position = player->pos;
    }

    else {
        if (CheckGroundCollision(&player->body, object)){
            player->onGround = 1;
            player->pos.y = player->pos.y + (result.sides_2.max.y - result.sides_1.min.y) + 0.001f;
        }
        
        player->pos = (Vector3){player->lastpos.x, player->pos.y, player->lastpos.z};

        player->body.position = player->pos;
        cam->position = player->pos;
    }

    EnableJump(player);
}

void EnableJump(Entity *player){
    static double accel = 0.0f;

    if (IsKeyPressed(KEY_SPACE) && player->onGround){
        player->onGround = 0;
        accel = 0.15f;
    }

    if (!player->onGround)
        player->pos.y += accel;
        
    else accel = 0.0f;
}