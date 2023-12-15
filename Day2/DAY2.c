#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int possibleGames(FILE*, int, int, int);
bool tryPlay(char*,int,int,int);
void powerOfGame(char*, int*, int*, int*);
int minimumCubes(FILE*);
int max(int, int);


int main()
{
    FILE *f;
    int pG, pow;

    f = fopen("input.txt", "r");

    pG = possibleGames(f,12,13,14);

    fclose(f);

    f = fopen("input.txt", "r");

    pow = minimumCubes(f);

    fclose(f);

    printf("For the bag content given there are %d possible games\nand there is %d sumofpowers\n", pG, pow);

    return 0;
}

int possibleGames(FILE* f, int red, int green, int blue)
{
    int game;
    int sumofgames = 0;
    int c;
    bool actualGame;
    char num[5] = {' '}; //We have to initialize this array whit size the max num of digits we can find together.
    int i;


    while(c!=EOF)
    {
        actualGame=true;
        game = -1;
        i=0;
        while((c = fgetc(f)) != ':')
        {       
            if(isdigit(c))
            {
                num[i]=c;
                i++;
            }
        }
        game = atoi(num);

        for(int j=0; num[j]!='\0'; j++)num[j]=' ';

        while(c != '\n' && c!= EOF)
        {
            i=0;
            char* play = (char*)malloc((i+1)*sizeof(char));
            while((c = fgetc(f)) != ';' && c != '\n' && c!= EOF)
            {       
                play[i]=c;
                i++;
                play = (char*)realloc(play, (i+1)*sizeof(char));
            }

            play[i]='\0';

            if(actualGame)
                actualGame = tryPlay(play, red, green, blue);

            free(play);
        }

        if(actualGame)
            sumofgames += game;
    }

    return sumofgames;
}

bool tryPlay(char* play, int r, int g, int b)
{
    char *types[] = {"red", "green", "blue"};
    char *cube;
    int i=0, k, numtotry;
    bool actPlay = true;

    while(play[i]!='\0')
    {
        k=0;
        char* act_cube = (char*)malloc((k+1)*sizeof(char));
        char*  endptr;
        while(play[i]!=',' && play[i]!='\0')
        {
            if(play[i]!=' ')
            {
                act_cube[k]=play[i];
                act_cube = (char*)realloc(act_cube,(k+1)*sizeof(char));
                k++;
            }
            i++;
        }
        act_cube[k]='\0';

        if(play[i]==',')
            i++;

        for(int j=0; j<3; j++)
        {
            if(((cube = strstr(act_cube,types[j])) != NULL))
            {
                numtotry = atoi(act_cube);

                switch(j)
                {
                    case 0:
                        actPlay = actPlay && (numtotry <= r);
                        break;
                    case 1:
                        actPlay = actPlay && (numtotry <= g);
                        break;
                    case 2:
                        actPlay = actPlay && (numtotry <= b);
                }
            }
        }
        
        free(act_cube);
    }
    
    return actPlay;
}

int minimumCubes(FILE *f)
{
    int game;
    int sumofpowers = 0;
    int c;
    int r, g, b;

    int i;


    while(c!=EOF)
    {
        i=0;
        r = g = b = 1;

        while((c = fgetc(f)) != ':');

        while(c != '\n' && c!= EOF)
        {
            i=0;
            char* play = (char*)malloc((i+1)*sizeof(char));
            while((c = fgetc(f)) != ';' && c != '\n' && c!= EOF)
            {       
                play[i]=c;
                i++;
                play = (char*)realloc(play, (i+1)*sizeof(char));
            }

            play[i]='\0';

            powerOfGame(play, &r, &g, &b);

            free(play);
        }

        sumofpowers += (r*g*b);
    }

    return sumofpowers;
}

void powerOfGame(char *play, int *r, int *g, int *b)
{
    char *types[] = {"red", "green", "blue"};
    char *cube;
    int i=0, k, numtotry;
    bool actPlay = true;

    while(play[i]!='\0')
    {
        k=0;
        char* act_cube = (char*)malloc((k+1)*sizeof(char));
        while(play[i]!=',' && play[i]!='\0')
        {
            if(play[i]!=' ')
            {
                act_cube[k]=play[i];
                act_cube = (char*)realloc(act_cube,(k+1)*sizeof(char));
                k++;
            }
            i++;
        }
        act_cube[k]='\0';

        if(play[i]==',')
            i++;

        for(int j=0; j<3; j++)
        {
            if(((cube = strstr(act_cube,types[j])) != NULL))
            {
                numtotry = atoi(act_cube);

                switch(j)
                {
                    case 0:
                        *r = max(*r, numtotry);
                        break;
                    case 1:
                        *g = max(*g, numtotry);
                        break;
                    case 2:
                        *b = max(*b, numtotry);
                }
            }
        }
        
        free(act_cube);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}