#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int firstAndLastDigit(char*, int);
int allCalibrationValues(FILE*); 
void letterToDigits(char *array);
int allCalibrationValuesP2(FILE* f);

int main()
{
    FILE* f;
    int n1, n2;

    f=fopen("input.txt","r");

    n1 = allCalibrationValues(f);

    fclose(f);

    f=fopen("input.txt","r");

    n2 = allCalibrationValuesP2(f);

    fclose(f);

    printf("The calibration of the full file in part one is %d\nbut in part two is %d\n", n1, n2);

    return 0;
}

int allCalibrationValues(FILE* f)
{
    int size, n, sum=0;
    char c;

    while(c!=EOF) //Control the end of the file.
    {
        size=1; //Initialize (or restart) the size of the array per line.
        char *array=(char *)malloc(size*sizeof(char));

        while((c=fgetc(f))!='\n' && c!=EOF)
        {
            array[size-1]=c;
            size++;
            array = (char *)realloc(array, size*sizeof(char));
        }
        array[size - 1]='\0';
        n = firstAndLastDigit(array, size); //Gets the calibration of the line.
        sum+=n; //And increments the acumulation of calibrations

        free(array); //Free the memory of the line to let other line allocate memory.
    }

    return sum;
}

int firstAndLastDigit(char* array, int size)
{
    int first=-1, last=-1;
    int i=0;

    while((first==-1 || last==-1) && i<size) //This while stops in the moment it finds the first and last digit.
    {
        if(isdigit(array[i]) && first==-1)
            first = array[i]-48;
    
        if(isdigit(array[size-i-1]) && last==-1)
            last = array[size-i-1]-48;
        
        i++;
    }

    return first*10+last;    
}

int allCalibrationValuesP2(FILE* f)
{
    int size, n, sum=0;
    char c;

    while(c!=EOF) //Control the end of the file.
    {
        size=1; //Initialize (or restart) the size of the array per line.
        char *array=(char *)malloc(size*sizeof(char));

        while((c=fgetc(f))!='\n' && c!=EOF)
        {
            array[size-1]=c;
            size++;
            array = (char *)realloc(array, size*sizeof(char));
        }
        array[size - 1]='\0';

        letterToDigits(array);

        n = firstAndLastDigit(array, size); //Gets the calibration of the line.
        sum+=n; //And increments the acumulation of calibrations

        free(array); //Free the memory of the line to let other line allocate memory.
    }

    return sum;
}

void letterToDigits(char *array)
{
    const char *numbers[] ={"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *coincidence = array;

    for(int i=0; i<9; i++)
    {
        while((coincidence = strstr(array, numbers[i])) != NULL)
        {
            coincidence[1] = i+1+48;  //It modifies the second digit of the letter number to avoid fail in cases two numbers uses the same letter ex: twone
        }
    }
}