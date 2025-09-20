#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef struct {
    Model model;
    Texture2D texture;
    
    Vector3 spawnpos;
    Vector3 vel;

    int HP;
} Entity;

#endif