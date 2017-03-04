#ifndef mesh_h_included
#define mesh_h_included

#include "Vector.h"

struct Mesh
{
    struct Vector3 verticles[1000];
    struct Vector3 objectRotation;
    struct Vector3 objectPosition;
    int trianglesCount;
};

#endif
