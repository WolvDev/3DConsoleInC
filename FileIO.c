#include "FileIO.h"

void LoadModel(char *file_name, struct Vector3 * verticles, int trianglesCount)
 {
   char buff[255];
   FILE *fp;
   fp = fopen("Cube.txt", "r");
   fgets(buff, 255, (FILE*)fp);

   int i = 0;
   int numbersCount = 0;
   int currentVerticle = 0;

   for(i=0;i<trianglesCount*3*3;i++)
   {
       fgets(buff, 255, (FILE*)fp);
       int value = 0;

         if(buff[0]=='-'){value = (buff[1] - '0')*-1;} else{value = (buff[0] - '0');}
           switch(numbersCount)
           {
            case 0:(verticles+currentVerticle)->x = value;numbersCount++;break;
            case 1:(verticles+currentVerticle)->y = value;numbersCount++;break;
            case 2:(verticles+currentVerticle)->z = value;numbersCount = 0;currentVerticle++;break;
           }
   }
 }

 int GetModelTrianglesCount(char *file_name)
 {
     return 72;
 }
