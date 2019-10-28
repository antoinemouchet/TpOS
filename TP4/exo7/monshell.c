#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


pid_t create_process(void)
{
    //create a process
    pid_t pid;


    do {
	pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));


    return pid;
}


int main(int argc, char const *argv[])
{
    char exit_key[] = "quit";
    int quit = 0;
    while (quit == 0)
    {
        
        char commande[300];
        
        // ask the command 
        printf("> ");
        scanf("%s", commande);
        
        //check if the user want to leave monshell
        if (strcmp(commande, exit_key) == 0)
        {
            quit = 1;
        }
        
        //run programm
        else
        { 
            pid_t son = create_process();
            
            switch (son)
            {   //error case
                case -1:
                    perror("fork");
                    return EXIT_FAILURE;
                //son case
                case 0:
                    system(commande);
                    break;
                //father case
                default:
                    wait(NULL);
                    break;
            }
        }
        
    }
    
    
    return 0;
}

