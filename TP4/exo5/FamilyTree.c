#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void DisplayPid(void)
{
    printf("My pid is: %d. Parent's pid is: %d.\n", getpid(), getppid());
}

int main(int argc, char const *argv[])
{
    int n1, n2 , n3;
    n1 = fork();
    n2 = fork();
    n3 = fork();
    
    //Father
    if (n1 > 0 && n2 > 0 && n3 > 0)
    {
        //wait the 3 direct kids
        wait(NULL);
        wait(NULL);
        wait(NULL);

        printf("I'm the father.\n");
        printf("My pid is: %d.\n", getpid());
    }

    //First child 1
    else if (n1 == 0 && n2 > 0 && n3 > 0)
    {   
        //Wait for children to die
        wait(NULL);
        wait(NULL);

        printf("I'm the first child.\n");
        DisplayPid();
    }

    //Second child 1
    else if (n1 > 0 && n2 == 0 && n3 > 0)
    {   
        //Wait its kid
        wait(NULL);

        printf("I'm the second child.\n");
        DisplayPid();
    }

    //Third child 1
    else if (n1 > 0 && n2 > 0 && n3 == 0)
    {
        printf("I'm the third child.\n");
        DisplayPid();
    }

    //First child 2 of first child 1
    else if (n1 == 0 && n2 == 0 && n3 > 0)
    {   
        //wait its kid
        wait(NULL);

        printf("I'm the fourth child.\n");
        DisplayPid();
    }

    //Second child 2 of first child 1
    else if (n1 == 0 && n2 > 0 && n3 == 0)
    {
        printf("I'm the fifth child.\n");
        DisplayPid();
    }

    //First child 2 of second child 1
    else if (n1 > 0 && n2 == 0 && n3 == 0)
    {
        printf("I'm the sixth child.\n");
        DisplayPid();
    }

    //First child 3 of first child 2 of first child 1
    else if (n1 == 0 && n2 == 0 && n3 == 0)
    {
        printf("I'm the seventh child.\n");
        DisplayPid();
    }
    
    //Error
    else
    {
        printf("There was an error generating new process.\n");
    }
    
    return 0;
}
