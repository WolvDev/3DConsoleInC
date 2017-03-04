#ifndef render_h_included
#define render_h_included


#include "Vector.h"
#include "Mesh.h"
#include "Camera.h"
#include <stdio.h>
#include <math.h>

void RenderMesh(struct Mesh * loadedMesh, char * ekran, struct Vector2 * screenSize, struct Camera * cam);
struct Vector2 TransformFromWorldToScreenPoint(struct Vector3 * point,struct Mesh * loadedMesh, struct Camera * cam,struct Vector2 *screenSize);
void SetCursorPosWIN(int XPos, int YPos);
struct Vector2 Normalize(struct Vector2 v);
void RenderVerticles(struct Vector3 *point,struct Mesh * loadedModel,char * buffor_ekranu,struct Vector2 * screenSize,struct Camera * cam);

#endif
