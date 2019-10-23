#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

    int n, pidCurr, pidFather;

    n = fork();

    //Père
    if (n > 0)
    {
        printf("Je suis le père. Pid:>>> %d\n", getpid());
        /* Utile pour attendre que le fils décède ce qui permet de ne pas avoir de problèmes
          si ce dernier demande des informations venant de père particulièrement. */
        //wait(NULL);
    }
    //Fils
    else if (n == 0)
    {
        printf("Je suis le fils. Pid:>>> %d\n\t\t Pid père:>>> %d\n", getpid(), getppid());
        //Fais en sorte que le processus fils s'arrête ici.
        //exit(0);
    }
    else
    {
        printf("Erreur");
        return 1;
    }
    return 0;
}
