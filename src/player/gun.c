#include "gun.h"

Gun CreateGun(Object *model, int ammo, bool isEquiped){
    Gun gun = {
        .model = *model,
        .ammo = ammo,
        .equiped = isEquiped
    };

    return gun;
}