#include "vector.h"

Vector3 _Vector3Normalize(Vector3 vector){
    Vector3 result = {0.0f, 0.0f, 0.0f};

    double vector_module = sqrt(
        (vector.x * vector.x) +
        (vector.y * vector.y) +
        (vector.z * vector.z)
    );

    if (vector_module > 0.0f){
        result.x = vector.x / vector_module;
        result.y = vector.y / vector_module;
        result.z = vector.z / vector_module;
    }

    return result;
}

Vector3 Vector3Sum(Vector3 vector1, Vector3 vector2){
    Vector3 result = {
        .x = vector1.x + vector2.x,
        .y = vector1.y + vector2.y,
        .z = vector1.z + vector2.z
    };

    return result;
}

Vector3 _Vector3Subtract(Vector3 vector1, Vector3 vector2){
    Vector3 result = {
        .x = vector1.x - vector2.x,
        .y = vector1.y - vector2.y,
        .z = vector1.z - vector2.z
    };

    return result;
}

Vector3 Vector3Cross(Vector3 vector1, Vector3 vector2){
    Vector3 result = {
        .x = vector1.y * vector2.z - vector1.z * vector2.y,
        .y = vector1.z * vector2.x - vector1.x * vector2.z,
        .z = vector1.x * vector2.y - vector1.y * vector2.x
    };

    return result;
}