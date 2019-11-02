#include <stdio.h>
#include <stdlib.h>
//#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
    int n, NbAlarm = 0;
    n = fork();

    //Child process
    if (n == 0)
    {
        //Loop
        while (1)
        {
            raise(SIGALRM);
            NbAlarm ++;
            //terminate child if 3 alarms sent
            if (NbAlarm == 3)
            {
                kill(getpid(), SIGTERM);
            } 
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
