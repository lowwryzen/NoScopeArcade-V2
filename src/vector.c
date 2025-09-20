#include "vector.h"

Vector3 AddVector3(Vector3 *first, Vector3 *second){
    Vector3 result = {0};
    
    result.x = first->x + second->x;
    result.y = first->y + second->y;
    result.z = first->z + second->z;

    return result;
}