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
    char sentence[250];
    char StopRolling[5] = "quit";
    int fd = open("./ReadHereMySon", O_RDWR|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    while(KeepRolling == 0)
    {
        // Ask sentence to write in the file
        printf("write something\n");
        scanf("%s", sentence);
        // Check the user want to leave the programm
        if (sentence == StopRolling)
        {
            KeepRolling = 1;
        }
        else
        {   
            //write sentence into fd
            int w = write(fd,  sentence, buffer);
            
            //Check if written correctly
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
        break;
    default:
        wait(NULL);
        break;
    }

    //Close file
    close(fd);
    
    return 0;
}
