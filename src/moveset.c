#include <math.h>

#include "raylib.h"

#include "moveset.h"
#include "vector.h"

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

    case IN_SCREEN:
        DisableCursor();
        status = LOCK;

        break;

    case OUT_SCREEN:
        EnableCursor();
        status = SUSPEND;
        break;

    case LOCK:
        movesetCamera(mouse);
        break;

    case SUSPEND:
        break;
    }
}

void movesetPlayer(Camera3D *camera){
    if (IsKeyDown(KEY_W)){
        camera->position.x += 0.1f;
    }
    
    if (IsKeyDown(KEY_S)){
        camera->position.x -= 0.1f;
    }

    if (IsKeyDown(KEY_A)){
        camera->position.z -= 0.1f;
    }

    if (IsKeyDown(KEY_D)){
        camera->position.z += 0.1f;
    }


    if (IsKeyPressed(KEY_SPACE)){
        // Jump system
    }
}

void movesetCamera(Camera3D *camera){
    Vector2 mouse_delta = GetMouseDelta();

    static float yaw = 0.0f;
    static float pitch = 0.0f;

    yaw += mouse_delta.x * 0.1f;
    pitch -= mouse_delta.y * 0.1f;

    if (pitch > 89.0f){pitch = 89.0f;}
    if (pitch < -89.0f){pitch = -89.0f;}

    Vector3 dislocation = {
        .x = cos(toradians(yaw)) * cos(toradians(pitch)),
        .y = sin(toradians(pitch)),
        .z = sin(toradians(yaw)) * cos(toradians(pitch))
    };

    camera->target = Vector3Sum(camera->position, _Vector3Normalize(dislocation));

    return;
}