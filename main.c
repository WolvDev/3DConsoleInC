#include "3DRender.h"
#include "DebugLog.h"
#include "FileIO.h"
#include "Ekran.h"
#include "Mesh.h"

int main(void)
{
    int fps = 0;
    int timePassed = 0;

    char ekran[120*30];
    struct Mesh cube;
    cube.trianglesCount = GetModelTrianglesCount("Cube.txt");
    cube.objectPosition.x = 0;
    cube.objectPosition.y = 0;
    cube.objectPosition.z = -40;

    struct Camera cam;
    cam.position.x = 0;
    cam.position.y = 0;
    cam.position.z = 0;

    struct Vector2 screenSize;
    screenSize.x = 120;
    screenSize.y = 30;

    LoadModel("Cube.txt",&cube.verticles[0],cube.trianglesCount);
    int testTime = 0;

    time_t startLoop;
    time_t currentLoop;
    time(&startLoop);
    time(&currentLoop);
    printf("Podaj dlugosc testu w sekundach:\n");
    scanf("%d",&testTime);


    while(currentLoop-startLoop < testTime+1)
    {
        time(&currentLoop);
        cube.objectRotation.x += 0.08f;
        cube.objectRotation.y += 0.06f;

       fps++;
       ClearBuffor(ekran,&screenSize);
       RenderMesh(&cube,ekran,&screenSize,&cam);
       printf("%s",ekran);
    }
    timePassed = currentLoop - startLoop;
    SaveResult(fps,timePassed);

    return 0;
}
