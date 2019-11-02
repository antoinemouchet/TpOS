#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int n, number = 1, success, looping = 1;
    char choice;

    n = fork();

    //Child case
    if (n == 0)
    {
        //Infinite loop
        while (1)
        {
            number += number;
            sleep(5);
        } 
    }
    //Father case
    else if (n > 0)
    {
        while (looping)
        {
            //Display menu
            printf("Insert:\n"
                    "-s to make son fall asleep.\n"
                    "-r to awake son.\n"
                    "-q to kill son.\n");

            //Get choice from user
            scanf("%c", &choice);

            switch (choice)
            {

            //Son asleep
            case 's':
                success = kill(n, SIGSTOP);

                //Make sure signal was sent
                if (!success)
                {
                    printf("Son was set asleep.\n");
                }
                else
                {
                    perror("There was an error: ");
                }

                break;

            //Awake son
            case 'r':
                success = kill(n, SIGCONT);

                //Make sure signal was sent
                if (!success)
                {
                    printf("Son was awaken sucesfully.\n");
                }
                else
                {
                    perror("There was an error: ");
                }
                break;

            //Kill son
            case 'q':
                success = kill(n, SIGTERM);

                //Make sure signal was sent
                if (!success)
                {
                    printf("Son was killed sucesfully.\n");
                }
                else
                {
                    perror("There was an error: ");
                }
                //End loop
                looping = 0;

                break;
            }
        }
        
        //End of process
        wait(NULL);
    }
    else
    {
        printf("There was an error generating the process.\n");
    }

    printf("End of program.\n");

    return 0;
}
