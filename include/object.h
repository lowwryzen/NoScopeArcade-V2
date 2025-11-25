#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

typedef struct {
    Model model;
    Texture2D texture;
    
    BoundingBox boundingbox;
    Vector3 position;

    float scale;
} Object;

typedef struct {
    BoundingBox sides_1;
    BoundingBox sides_2;
} Two_Sides;

void InitObject(Object *object);
void DelObject(Object *object);

Two_Sides aabbCollision(Object object1, Object object2);

bool CheckCollision(Object object1, Object object2);
bool CheckGroundCollision(Object object1, Object object2);

#endif