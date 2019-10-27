#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h> 
int create_process(void) 
{
    int ;
    do 
    {

        pid = fork()

    } 
    while ((pid == -1) && (errno == EAGAIN))
    
    return pid;
}
int main(int argc, char const *argv[])
{   int nb_son, son_pid, random_number
    srand(time(NULL));
    for (nb_son = 0; nb_son <= 4, nb_son++ )
    { 
        printf("Fils numéro %i", nb_son);
        int n = create_process();

        switch (n)
        {
        case -1:
            perror("fork");
            return EXIT_FAILURE;
        
        case 0:
            random_number = rand();
            son_pid = getpid()
            printf("Je suis le fils, mon PID est %d et mon nombre est %d /n" son_pid, random_number);
            break;
        
        default:
            wait(NULL)
            printf("Je suis le pere, mon PID est %d , celui de mon fils est %d et son nombre est %d" pid_t getpid(), son_pid, random_number);

            break;
        }
    }
    return 0;
}
