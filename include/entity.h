#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "object.h"
#include "gun.h"

typedef struct {
    Object body;
    Gun gun;

    Vector3 pos;
    Vector3 lastpos;
    
    int HP;
    float vel;
    float velY;

    bool onGround;
    bool isAlive;
    
} Entity;

Entity CreateEntity(Object body, Vector3 pos, int HP, float vel, bool isAlive);
Camera3D CreateCamera(Vector3 position, Vector3 target, Vector3 up);
#endif