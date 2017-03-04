#ifndef ekran_h_included
#define ekran_h_included

#include "Vector.h"


void DrawPixel(struct Vector2 *pos, char * ekran,struct Vector2 * screenSize);
void ClearBuffor(char * ekran,struct Vector2 * screenSize);
void DrawBuffor(char * ekran,struct Vector2 * screenSize);


#endif
