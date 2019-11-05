#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int SigReceived = 0;

void handler(int signum)
{
    printf("Signal received: %d\n", signum);
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
        struct sigaction act;
        act.sa_handler = handler;

        //Loop to change for every signal
        for (int i = 1; i < 33; i++)
        {
            sigaction(i, &act, NULL);
        }
        //Loop until signal is received
        while (!SigReceived)
        {
            pause();
        }
        printf("Child is done (pid: %d).\n", getpid());
    }

    else
    {
        //Sleep 5 seconds
        sleep(5);
        //Send signal to child
        kill(forkReturn, SIGUSR1);

        //Sleep 5 seconds
        sleep(5);
        //Send second signal to child
        kill(forkReturn, SIGUSR2);

        //Wait for child to finish
        wait(NULL);
        printf("Dad is done (pid: %d).\n", getpid());
    }

    return 0;
}
