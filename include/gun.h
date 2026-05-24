#ifndef GUN_H
#define GUN_H

#include "raylib.h"

#include "object.h"

typedef struct{
    Object model;

    int ammo;
    bool equiped;
} Gun;

Gun CreateGun(Object *model, int ammo, bool isEquiped);

#endif