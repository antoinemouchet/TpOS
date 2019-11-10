#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 


#define FILE_SIZE 1024

int main(int argc, char const *argv[])
{
    ssize_t nrd;
    int fd;
    int fd1;
    
    // Check that the good amount of arguments was given.
    if (argc != 3)
    {
        printf("Wrong amount of arguments. 2 doc names waited.\n");
        // Error case
        return 1;
    }
    
    //Opening files
    fd = open(argc[1], O_RDONLY);
    fd1 = open(argc[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    
    //Write fd into fd1
    while (nrd = read(fd,buffer,50)) 
    {
        write(fd1,buffer,nrd);
    }
    
    //Closing files
    close(fd);
    close(fd1);


    return 0;
}
