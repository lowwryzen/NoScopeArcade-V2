#include <math.h>

#include "raylib.h"

#include "moveset.h"
#include "vector.h"

static float yaw = 0.0f;
static float pitch = 0.0f;

static Vector3 dislocation = {0};

float player_speed = 0.1f;
float sensi = 0.1f;

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
        camera->position = Vector3Sum(camera->position, (Vector3){(dislocation.x * player_speed), 0.0f, (dislocation.z * player_speed)});
    }
    
    if (IsKeyDown(KEY_S)){
        camera->position = _Vector3Subtract(camera->position, (Vector3){(dislocation.x * player_speed), 0.0f, (dislocation.z * player_speed)});
    }

    if (IsKeyDown(KEY_A)){
        Vector3 side_vector = _Vector3Normalize(Vector3Cross(dislocation, camera->up));

        camera->position = _Vector3Subtract(camera->position, (Vector3){(side_vector.x * player_speed), (side_vector.y * player_speed), (side_vector.z * player_speed)});
    }

    if (IsKeyDown(KEY_D)){
        Vector3 side_vector = _Vector3Normalize(Vector3Cross(dislocation, camera->up));

        camera->position = Vector3Sum(camera->position, (Vector3){(side_vector.x * player_speed), (side_vector.y * player_speed), (side_vector.z * player_speed)});
    }


    if (IsKeyPressed(KEY_SPACE)){
        // Jump system
    }
}

void movesetCamera(Camera3D *camera){
    Vector2 mouse_delta = GetMouseDelta();

    yaw += mouse_delta.x * sensi;
    pitch -= mouse_delta.y * sensi ;

    if (pitch > 89.0f){pitch = 89.0f;}
    if (pitch < -89.0f){pitch = -89.0f;}

    dislocation.x = cos(toradians(yaw)) * cos(toradians(pitch));
    dislocation.y = sin(toradians(pitch));
    dislocation.z = sin(toradians(yaw)) * cos(toradians(pitch));

    camera->target = Vector3Sum(camera->position, _Vector3Normalize(dislocation));

    return;
}