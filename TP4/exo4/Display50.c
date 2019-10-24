#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void displayGenerationError()
{
    printf("There was an error generating new process.\n");
}

int main(int argc, char const *argv[])
{
    int n1 = fork();

    if (n1 < 0)
    {
        displayGenerationError();
    }
    else if (n1 == 0)
    {
        //Display number of first child
        printf("\nFirst child: ")
        for (int i = 1; i < 26; i++)
        {
            printf("%d ", i);
        }
        exit();
    }
    //Father case
    else
    {
        //Wait for first child to die
        wait(NULL);
        //Create second process
        int n2 = fork();

        //Child case
        if (n2 == 0)
        {
            //Display numbers of second child
            printf("\nSecond child: ")
            for (int i = 26; i < 51; i++)
            {
                printf("%d ", i);
            }
            //Terminate child when numbers printed
            exit();
        }
        //Error case
        else if (n2 == -1)
        {
            displayGenerationError();
        }   
    }
    printf("Dad is here.\n")
    return 0;
}
