#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "object.h"

typedef struct {
    Object body;
    Vector3 pos;
    
    int HP;
    float vel;

    bool onGround;
    bool isAlive;
    
} Entity;

#endif