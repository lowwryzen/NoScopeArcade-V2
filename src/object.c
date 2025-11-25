#include "raylib.h"
#include "object.h"

void InitObject(Object *object){
    object->model.materials->maps[MATERIAL_MAP_DIFFUSE].texture = object->texture;
    
    DrawModel(object->model, object->position, object->scale, RAYWHITE);
}

void DelObject(Object *object){
    UnloadTexture(object->texture);
    UnloadModel(object->model);
}

Two_Sides aabbCollision(Object object1, Object object2){
    BoundingBox sides_1 = {
        .min.x = (object1.boundingbox.min.x * object1.scale) + object1.position.x,
        .min.y = (object1.boundingbox.min.y * object1.scale) + object1.position.y,
        .min.z = (object1.boundingbox.min.z * object1.scale) + object1.position.z,
        
        .max.x = (object1.boundingbox.max.x * object1.scale) + object1.position.x,
        .max.y = (object1.boundingbox.max.y * object1.scale) + object1.position.y,
        .max.z = (object1.boundingbox.max.z * object1.scale) + object1.position.z
    };

    BoundingBox sides_2 = {
        .min.x = (object2.boundingbox.min.x * object2.scale) + object2.position.x,
        .min.y = (object2.boundingbox.min.y * object2.scale) + object2.position.y,
        .min.z = (object2.boundingbox.min.z * object2.scale) + object2.position.z,
        
        .max.x = (object2.boundingbox.max.x * object2.scale) + object2.position.x,
        .max.y = (object2.boundingbox.max.y * object2.scale) + object2.position.y,
        .max.z = (object2.boundingbox.max.z * object2.scale) + object2.position.z
    };

    Two_Sides result = {sides_1, sides_2};

    return result;
}

bool CheckCollision(Object object1, Object object2){
    Two_Sides result = aabbCollision(object1, object2);

    return (
        result.sides_1.max.x >= result.sides_2.min.x && result.sides_1.min.x <= result.sides_2.max.x &&
        result.sides_1.max.y >= result.sides_2.min.y && result.sides_1.min.y <= result.sides_2.max.y &&
        result.sides_1.max.z >= result.sides_2.min.z && result.sides_1.min.z <= result.sides_2.max.z
    );
}

bool CheckGroundCollision(Object object1, Object object2){
    Two_Sides result = aabbCollision(object1, object2);

    return (
        result.sides_1.min.x <= result.sides_2.max.x && result.sides_1.max.x >= result.sides_2.min.x &&
        result.sides_1.min.y <= result.sides_2.max.y && result.sides_1.max.y >= result.sides_2.min.y && 
        result.sides_1.min.z <= result.sides_2.max.z && result.sides_1.max.z >= result.sides_2.min.z
    );
}