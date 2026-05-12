#include "entity.h"

Entity CreateEntity(Object body, Vector3 pos, int HP, float vel, bool isAlive){
    Entity entity = {
        .body = body,
        .pos = pos,
        .HP = HP,
        .vel = vel,
        .isAlive = isAlive
    };

    return entity;
}

Camera3D CreateCamera(Vector3 position, Vector3 target, Vector3 up){
    Camera3D cam = {
        .fovy=45.0f,
        .position=   position,
        .target=     target,
        .up=         up,
        .projection= CAMERA_PERSPECTIVE,
    };

    return cam;
}