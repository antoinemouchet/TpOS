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
    //Generate first child
    int n1 = fork(); 
  
    //Child case
    if (n1 == 0)
    {
        printf("I'm the first child. My pid is: %d. \
        Parent's pid is: %d.\n", getpid(), getppid());

        //Generate first child of first child
        int n14 = fork();

        //3 childs processes here
        wait(NULL);
        wait(NULL);
        wait(NULL);

        //Child case
        if (n14 == 0)
        {
            //1child
            wait(NULL);

            printf("I'm the fourth child. My pid is: %d. \
            Parent's pid is: %d.\n", getpid(), getppid());

            //Child of child of child
            int n147 = fork();
            if (n147 == 0)
            {
                printf("I'm the seventh child. My pid is: %d. \
                Parent's pid is: %d.\n", getpid(), getppid());
                exit(0);
            }
            //Error
            else if (n147 < 0)
            {
                displayGenerationError();
            }
            //Parent case
            else
            {
                exit(0);
            }
            
        }

        //Parent case
        else if (n14 > 0)
        {
            //Child of child
            int n15 = fork();

            wait(NULL);

            //Child case
            if (n15 == 0)
            {
                printf("I'm the fifth child. My pid is: %d. \
                Parent's pid is: %d.\n", getpid(), getppid());
                exit(0);
            }
            //Error
            else if (n15 < 0)
            {
                displayGenerationError();
            }
            //Parent case
            else
            {
                exit(0);
            }  
        }
        //Error case
        else
        {
            displayGenerationError();
        }
        
    } 
    //Parent case in first child
    else if (n1 > 0)
    {
        //Second child
        int n2 = fork(); 

        wait(NULL);

        //Child case
        if (n2 == 0)
        {
            printf("I'm the second child. My pid is: %d. \
            Parent's pid is: %d.\n", getpid(), getppid());

            //Child of child
            int n16 = fork();
            
            //Child case
            if (n16 == 0)
            {
                printf("I'm the sixth child. My pid is: %d. \
                Parent's pid is: %d.\n", getpid(), getppid());
                exit(0);
            }
            //Error
            else if (n16 < 0)
            {
                displayGenerationError();
            }
            //Parent case
            else
            {
                exit(0);
            }
        }

        //Parent case in first and second child
        else if (n2 > 0)
        {
            //Third child
            int n3 = fork(); 
            if (n3 == 0)
            { 
                printf("I'm the third child. My pid is: %d. \
                Parent's pid is: %d.\n", getpid(), getppid());
                exit(0);
            } 
  
            //Parent process
            else if (n3 > 0)
            {
                printf("I'm the father, my pid is: %d\n", getpid());
            }
            //Error case
            else
            {
                displayGenerationError();
            }
        }
    }
    else
    {
        displayGenerationError();
    }
    
    return 0;
}
