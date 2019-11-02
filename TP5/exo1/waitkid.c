#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int NbAlarm = 0;

void handler(int signum)
{
    //increment nb alarms and print amount of times it was already printed
    NbAlarm ++;
    printf("Number of alarms: %d.\n", NbAlarm);
}

int main(int argc, char const *argv[])
{


    int n;
    n = fork();

    //Child process
    if (n == 0)
    {
        //modify action of sigalrm and ignore all signals except it
        struct sigaction act;
        sigset_t set;
        act.sa_handler = handler;
        act.sa_flags = 0;
        sigaction(SIGALRM, &act, NULL);
        sigfillset(&set);
        sigdelset(&set, SIGALRM);
        sigprocmask(SIG_SETMASK, &set, NULL);

        //Loop
        while (1)
        {
            //Send signal
            kill(getpid(), SIGALRM);
            //terminate child if 3 alarms sent
            if (NbAlarm == 3)
            {
                kill(getpid(), SIGKILL);
            }
            sleep(3);
        }   
    }

    //Parent process
    else if (n > 0)
    {
        //Wait for child
        wait(NULL);
        printf("Dad here.\n");
    }
    else
    {
        printf("There was an error generating the process.\n");
    }
    
    return 0;
}
