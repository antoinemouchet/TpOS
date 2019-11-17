#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h> 
#include <errno.h>

int main(int argc, char const *argv[])
{
    int pid, fpipe[2];
    //create pipe
    if (pipe(fpipe) == 0)
    {
        
        //make ls and sort at the same time
        pid = fork();
        int ftxt;
        switch (pid)
        {
            case -1:
                perror("fork");

                return 1;
            case 0:
                //son case 
                //execute ls 
                //reading the file in the pipe
                close(fpipe[0]);
                // receive the input 
                dup2(fpipe[1], STDOUT_FILENO); 
                execlp("ls", "ls", NULL);
                //close pipe
                close(fpipe[1]);
                break;
            default:
                //father case
                //execute sort -d                
                //writing in the pipe
                close(fpipe[1]);

                ftxt = open("file.txt", O_WRONLY);
                // send an input in the pipe 
                dup2(fpipe[0], STDIN_FILENO); 
                //send file.txt to the son in the pipe 
                dup2(ftxt, STDOUT_FILENO); 
                execlp("sort", "sort", "-d", NULL);
                
                
                //Close file and pipe 
                close(fpipe[0]);
                close(ftxt);
                
                break;
    
        }
    }

    else
    {
        perror("pipe");
        return 2;
    }
    return 0;
    // RETURN 0 IF SUCESS, 1 IF FORK ERROR, 2 IF PIPE ERROR
}
