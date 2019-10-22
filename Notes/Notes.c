#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

    int n, pidCurr, pidFather;

    n = fork();
    pidCurr = getpid();
    pidFather = getppid();

    if (n > 0)
    {
        printf("Je suis le père. Pid:>>> %d\n", pidCurr);
    }
    else if (n == 0)
    {
        printf("Je suis le fils. Pid:>>> %d\n\t\t Pid père:>>> %d", n, pidFather);
    }
    else
    {
        printf("Erreur");
        return 1;
    }
    return 0;
}
