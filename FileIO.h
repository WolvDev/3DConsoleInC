#ifndef file_h_included
#define file_h_included

#include <stdio.h>
#include "Vector.h"

void LoadModel(char *file_name, struct Vector3 * verticles, int trianglesCount);
int GetModelTrianglesCount(char *file_name);

#endif
