#include "Ekran.h"

void DrawPixel(struct Vector2 *pos, char * ekran,struct Vector2 * screenSize)
{
    if (pos->x < screenSize->x && pos->y < screenSize->y && pos->x>=0 && pos->y>=0)
	{
      int i = (int)pos->y*(int)screenSize->x + (int)pos->x;
      *(ekran+i) = 'X';
	}
}

void ClearBuffor(char * ekran,struct Vector2 * screenSize)
{
   int i = 0;
   for(i = 0;i<(screenSize->x*screenSize->y);i++)
   {
     *(ekran+i) = ' ';
   }
}

void DrawBuffor(char * ekran,struct Vector2 * screenSize)
{
   int i = 0;
   for(i = 0;i<screenSize->x*screenSize->y;i++)
   {
     //printf("%s",ekran);
   }
}
