#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    //Initialize variables
    char string[200], FileName[200], writing[400], counting[400];
    int n;

    //Get string
    printf("Insert the string to place into file:\n>>> ");
    scanf("%s",string);

    //Get file
    printf("What's the name of the file to write?\n>>> ");
    scanf("%s",FileName);

    n = fork();
    
    //Child
    if (n == 0)
    {
        //Writing is the command to execute as a string
        sprintf(writing, "echo %s > %s ", string, FileName);

        //Actual writing in the file
        char *array[3];
        array[0] = "sh";
        array[1] = "-c";
        array[2] = writing;
        array[3] = NULL;
        execvp(array[0],array);
    }

    //Parent
    else if (n > 0)
    {
        //wait for the child
        wait(NULL);

        //Define command to execute
        sprintf(counting, "wc %s", FileName);

        //Actual execution of command
        char *array[3];
        array[0] = "sh";
        array[1] = "-c";
        array[2] = counting;
        array[3] = NULL;
        execvp(array[0],array);

    }
    
    //Error 
    else
    {
        printf("There was a problem creating the new process.");
    }

    return 0;
}