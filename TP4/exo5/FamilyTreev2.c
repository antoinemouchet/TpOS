#include <stdio.h>
#include <stdlib.h>
//#include <sys/wait.h>
#include <unistd.h>

void DisplayPid(void)
{
    printf("My pid is: %d. Parent's pid is: %d.\n", getpid(), getppid());
}


int main(int argc, char const *argv[])
{
    int n1, n2, n3;
    n1 = fork();
    n2 = fork();
    n3 = fork();
    
    if (n1 > 0 && n2 > 0 && n3 > 0)
    {
        printf("I'm the father.");
        DisplayPid();
    }
    else if (n1 == 0 && n2 > 0 && n3 > 0)
    {
        printf("I'm the first child.\n");
        DisplayPid();
    }
    else if (n1 == 0 && n2 == 0 && n3 > 0)
    {
       // 
    }
    else if (n1 == 0 && n2 == 0 && n3 == 0)
    {
        printf("I'm the seventh child.\n");
        DisplayPid();
    }
    else
    {
        printf("I'm a child.\n");
        DisplayPid();
    }
    
    return 0;
}
