#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int NbAlarm = 0;

void handler(int signum)
{
    if (signum == SIGALRM)
    {
        NbAlarm ++;
    }
}

int main(int argc, char const *argv[])
{
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;

    int n;
    n = fork();

    //Child process
    if (n == 0)
    {
        //Loop
        while (1)
        {
            raise(SIGALRM);
            sigaction(SIGALRM, &act, NULL);
            //terminate child if 3 alarms sent
            if (NbAlarm == 3)
            {
                kill(getpid(), SIGTERM);
            } 
            printf("Alarm done");
            sleep(3);
        }   
    }

    //Parent process
    else if (n > 0)
    {
        //Wait for child
        wait(NULL);
    }
    else
    {
        printf("There was an error generating the process.\n");
    }
    
    return 0;
}
