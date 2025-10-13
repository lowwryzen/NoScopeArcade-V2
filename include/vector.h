#ifndef VECTOR_H
#define VECTOR_H

#include "raylib.h"

Vector3 _Vector3Normalize(Vector3 vector);
Vector3 Vector3Sum(Vector3 vector1, Vector3 vector2);
Vector3 _Vector3Subtract(Vector3 vector1, Vector3 vector2);
Vector3 Vector3Cross(Vector3 vector1, Vector3 vector2);

#endif