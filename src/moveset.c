#include <math.h>

#include "raylib.h"
#include "moveset.h"
#include "vector.h"

void movesetMouse(Camera3D *mouse){
    static unsigned char status = SUSPEND;

    float sensix;
    float sensiy;

    Vector2 camera_position;

    if (IsKeyPressed(KEY_TAB)){
        if (status == LOCK){
            status = OUT_SCREEN;
        }
        else if (status == OUT_SCREEN || SUSPEND){
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
        camera_position = GetMouseDelta();

        Vector2 camera_rad = {
            (camera_position.x) * PI / 180.0f,
            (camera_position.y) * PI / 180.0f
        };

        Vector3 dislocation = {
            .x = cosf(camera_rad.x) * sinf(camera_rad.y),
            .y = sinf(camera_rad.x),
            .z = cosf(camera_rad.x) * cosf(camera_rad.y)
        };

        //sensix = camera_position.x * PI / 180.0f;
        //sensiy = camera_position.y * PI / 180.0f;


        mouse->target = (Vector3){
            .x = (mouse->target.x + camera_position.x),
            .y = (mouse->target.y + camera_position.y),
            .z = (mouse->target.z + (camera_position.x + camera_position.y))
        };

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