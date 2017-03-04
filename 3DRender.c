#include "3DRender.h"
#include <math.h>
#include "Ekran.h"


void RenderMesh(struct Mesh * loadedMesh, char * ekran, struct Vector2 * screenSize, struct Camera * cam)
{
    unsigned int i = 0;
    for (i = 0; i < loadedMesh->trianglesCount; i++)
	{
		struct Vector3 points[3];
        points[0] = loadedMesh->verticles[i * 3];
		points[1] = loadedMesh->verticles[(i * 3)+1];
		points[2] = loadedMesh->verticles[(i * 3)+2];

		struct Vector3 rotatedPointsZ[3];
		struct Vector3 rotatedPointsX[3];
		struct Vector3 rotatedPointsY[3];

        int rO = 0;
		for (rO = 0;rO < 3;rO++)
		{
			rotatedPointsZ[rO].x = ((points[rO].x-0) *cos(loadedMesh->objectRotation.z* 3.14159 / 180.0)) - ((points[rO].y-0) * sin(loadedMesh->objectRotation.z* 3.14159 / 180.0)+0);
			rotatedPointsZ[rO].y = ((points[rO].x-0) *sin(loadedMesh->objectRotation.z* 3.14159 / 180.0)) + ((points[rO].y-0) * cos(loadedMesh->objectRotation.z* 3.14159 / 180.0)+0);
			rotatedPointsZ[rO].z = points[rO].z;
		}

		for (rO = 0;rO < 3;rO++)
		{
			rotatedPointsX[rO].y = ((rotatedPointsZ[rO].y-0) *cos(loadedMesh->objectRotation.x* 3.14159 / 180.0)) - ((rotatedPointsZ[rO].z-0) * sin(loadedMesh->objectRotation.x* 3.14159 / 180.0)+0);
			rotatedPointsX[rO].z = ((rotatedPointsZ[rO].y-0) *sin(loadedMesh->objectRotation.x* 3.14159 / 180.0)) + ((rotatedPointsZ[rO].z-0) * cos(loadedMesh->objectRotation.x* 3.14159 / 180.0)+0);
			rotatedPointsX[rO].x = rotatedPointsZ[rO].x;
		}

		for (rO = 0;rO < 3;rO++)
		{
			rotatedPointsY[rO].z = ((rotatedPointsX[rO].z-0) *cos(loadedMesh->objectRotation.y* 3.14159 / 180.0)) - ((rotatedPointsX[rO].x-0) * sin(loadedMesh->objectRotation.y* 3.14159 / 180.0)+0);
			rotatedPointsY[rO].x = ((rotatedPointsX[rO].z-0) *sin(loadedMesh->objectRotation.y* 3.14159 / 180.0)) + ((rotatedPointsX[rO].x-0) * cos(loadedMesh->objectRotation.y* 3.14159 / 180.0)+0);
			rotatedPointsY[rO].y = rotatedPointsX[rO].y;
		}

		rotatedPointsY[0].x += loadedMesh->objectPosition.x;rotatedPointsY[0].y += loadedMesh->objectPosition.y;rotatedPointsY[0].z += loadedMesh->objectPosition.z;
		rotatedPointsY[1].x += loadedMesh->objectPosition.x;rotatedPointsY[1].y += loadedMesh->objectPosition.y;rotatedPointsY[1].z += loadedMesh->objectPosition.z;
		rotatedPointsY[2].x += loadedMesh->objectPosition.x;rotatedPointsY[2].y += loadedMesh->objectPosition.y;rotatedPointsY[2].z += loadedMesh->objectPosition.z;

		RenderVerticles(&rotatedPointsY[0],loadedMesh,ekran,screenSize,cam);
	}
}
struct Vector2 TransformFromWorldToScreenPoint(struct Vector3 * point,struct Mesh * loadedMesh, struct Camera * cam,struct Vector2 *screenSize)
{
    struct Vector3 c = cam->position;
	struct Vector3 angles = loadedMesh->objectPosition;

	struct Vector3 radians;
	radians.x = angles.x * (3.14159f / 180);
	radians.y = angles.y * (3.14159f / 180);
	radians.z = angles.z * (3.14159f / 180);

	float x = point->x - c.x;
	float y = point->y - c.y;
	float z = point->z - c.z;

	float z_leng = x*x + y*y + z*z / 100.0f;

	float xDir = (cos(radians.y)*((sin(radians.z)*y) + (cos(radians.z)*x))) - sin(radians.y)*z;
	float yDir = (sin(radians.x)*((cos(radians.y)*z) + (sin(radians.y)*((sin(radians.z)*y) + (cos(radians.z)*x))))) + (cos(radians.x)*((cos(radians.z)*y) - (sin(radians.z)*x)));
	float zDir = (cos(radians.x)*((cos(radians.y)*z) + (sin(radians.y)*((sin(radians.z)*y) + (cos(radians.z)*x))))) - (sin(radians.x)*((cos(radians.z)*y) - (sin(radians.z)*x)));

	float average_len = 3.14159f * 55;
	struct Vector2 screenPoint;

    if (zDir != 0)
    {
			screenPoint.x = round(xDir * (average_len / zDir));
			screenPoint.y = round(yDir * (average_len / zDir));
			screenPoint.x += (screenSize->x - 1.0) / 2.0;
			screenPoint.y += (screenSize->y) / 2.0;
    }

return screenPoint;
}

struct Vector2 Normalize(struct Vector2 v)
{
	float lenght = sqrt((v.x*v.x) + (v.y*v.y));

	struct Vector2 normalized = v;
	if (lenght == 0)
	{
		normalized.x = 0;
		normalized.y = 0;
	}
	else
	{
		normalized.x = v.x / lenght;
		normalized.y = v.y / lenght;
	}

	return normalized;
}

void RenderVerticles(struct Vector3 * point, struct Mesh * loadedModel,char * buffor_ekranu,struct Vector2 * screenSize,struct Camera * cam)
{
        struct Vector2 screenPoints[3];
        struct Vector2 screenPointsNormalized[3];
		screenPoints[0] = TransformFromWorldToScreenPoint(point,loadedModel,cam,screenSize);
		screenPoints[1] = TransformFromWorldToScreenPoint((point+1),loadedModel,cam,screenSize);
		screenPoints[2] = TransformFromWorldToScreenPoint((point+2),loadedModel,cam,screenSize);

		struct Vector2 directions[3];
		struct Vector2 test[3];
		test[0].x = screenPoints[1].x - screenPoints[0].x;test[0].y = screenPoints[1].y - screenPoints[0].y;
		test[1].x = screenPoints[2].x - screenPoints[1].x;test[1].y = screenPoints[2].y - screenPoints[1].y;
		test[2].x = screenPoints[2].x - screenPoints[0].x;test[2].y = screenPoints[2].y - screenPoints[0].y;
		screenPointsNormalized[0] = Normalize(test[0]);
		screenPointsNormalized[1] = Normalize(test[1]);
		screenPointsNormalized[2] = Normalize(test[2]);


		DrawPixel(&screenPoints[0],buffor_ekranu,screenSize);
		DrawPixel(&screenPoints[1],buffor_ekranu,screenSize);
		DrawPixel(&screenPoints[2],buffor_ekranu,screenSize);


		int step[3];
		if (screenPointsNormalized[0].x != 0)
		{
			step[0] = (int)((screenPoints[1].x - screenPoints[0].x) / screenPointsNormalized[0].x);
		}
		else if (screenPointsNormalized[0].y != 0)
		{
			step[0] = (int)((screenPoints[1].y - screenPoints[0].y) / screenPointsNormalized[0].y);
		}
		else
		{
			step[0] = 0;
		}

		if (screenPointsNormalized[1].x != 0)
		{
			step[1] = (int)((screenPoints[2].x - screenPoints[1].x) / screenPointsNormalized[1].x);
		}
		else if (screenPointsNormalized[1].y != 0)
		{
			step[1] = (int)((screenPoints[2].y - screenPoints[1].y) / screenPointsNormalized[1].y);
		}
		else
		{
			step[1] = 0;
		}
		if (screenPointsNormalized[2].x != 0)
		{
			step[2] = (int)((screenPoints[2].x - screenPoints[0].x) / screenPointsNormalized[2].x);
		}
		else if (screenPointsNormalized[2].y != 0)
		{
			step[2] = (int)((screenPoints[2].y - screenPoints[0].y) / screenPointsNormalized[2].y);
		}
		else
		{
			step[2] = 0;
		}



        int vertexCount = 0;
		for (vertexCount = 0;vertexCount < 2;vertexCount++)
		{
		    int i = 0;
            for (i = 0;i < step[vertexCount]-1;i++)
			{
				 screenPoints[vertexCount].x += screenPointsNormalized[vertexCount].x; screenPoints[vertexCount].y += screenPointsNormalized[vertexCount].y;
				 screenPoints[vertexCount].x = screenPoints[vertexCount].x; screenPoints[vertexCount].y = screenPoints[vertexCount].y;

				 DrawPixel(&screenPoints[vertexCount],buffor_ekranu,screenSize);
			}
		}
}


