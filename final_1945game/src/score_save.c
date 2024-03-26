#include "myheader.h"

void ScoreFileLoad (int* Score)
{

    FILE *file = fopen("./score.txt", "r");
      
        
    fscanf(file, "%d \n", Score);
        

    fclose(file);

}

void ScoreFileSave (int Score)
{   
    FILE *file = fopen("./score.txt", "w");
        fprintf(file, "%d \n", Score);
        fclose(file);


}