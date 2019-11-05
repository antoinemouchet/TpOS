#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int SigReceived = 0;

void handle(int signum)
{
    printf("Signal received: %d", signum);
    if (signum == SIGUSR2)
    {
        SigReceived = 1;
    } 
}


int main(int argc, char const *argv[])
{
    int forkReturn;

    // Create a child process
    forkReturn = fork();

    // Error
    if (forkReturn < 0)
    {
        perror("An Error occured: ");
        // Error creating child process
        return 1;
    }
    // Child case
    else if (forkReturn == 0)
    {
        
    }
    
    return 0;
}
