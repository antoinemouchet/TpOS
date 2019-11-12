#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/wait.h>


#define buffer 1024

int main(int argc, char const *argv[])
{
    int KeepRolling = 0;
    
    char StopRolling[] = "quit\n";
    int fd = open("./ReadHereMySon", O_RDWR|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    while(KeepRolling == 0)
    {
        // Reset sentence
        char sentence[buffer] = "";

        // Ask sentence to write in the file
        printf("write something\n");
        // Get input from keyboard until enter is pressed
        int n = read(STDIN_FILENO, sentence, buffer);
        
        // Check if the user wants to leave the programm
        if (strcmp(sentence, StopRolling) == 0)
        {
            KeepRolling = 1;
        }
        else
        {   
            // write sentence into fd
            int w = write(fd,  sentence, n);
            
            // Check if written correctly
            if (w == -1)
            {
                printf("error");
                return 1;
            }
        }
    }

    //wc 
    int MySonIsReading = fork();
    char command[65];

    switch (MySonIsReading)
    {
    case -1:
        perror("fork");
        return 2;
    
    //son case
    case 0: 
        //using wc linux command
        strcpy(command, "wc ReadHereMySon"); /* .txt ? */
        system(command);
        exit(0);
    default:
        wait(NULL);
        break;
    }

    //Close file
    close(fd);
    
    return 0;
}
