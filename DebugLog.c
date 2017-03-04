#include "DebugLog.h"

void SaveResult(int frames, int timePassed)
{
   char buff[255];

   FILE *fp;
   fp = fopen("Log.txt","w");
   if( fp )
    {
        if(timePassed>0)
        {
          fprintf(fp,"Frames per second:%d\n",frames/timePassed);
        }
        else
        {
            fprintf(fp,"Frames per second:%d\n",frames);
        }
		fprintf(fp,"Time passed: %d seconds\n",(timePassed-1));
//		fprintf(fp,"Triangle count: %d\n",trianglesCount);

        fclose( fp );
    }
    else
    {
        printf("Can't open a log file");
    }


#ifdef _WIN32
	system("cls");
#else
	printf("\033[2J");
#endif

    printf("Obraz byl wyswietlany ze srednia czestotliwoscia %d klatek na sekunde.\n",frames/timePassed );
    printf("Wynik testu znajduje sie w pliku Log.txt\n");

#ifdef _WIN32
	system("PAUSE");
#endif
}


