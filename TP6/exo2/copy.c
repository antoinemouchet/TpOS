#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    ssize_t n;
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
    fd = open(argv[1], O_RDONLY);

    // Get stats from original file
    struct stat statfile;
    stat(argv[1], &statfile);

    // Create document in which we want to copy
    fd1 = open(argv[2], O_CREAT | O_WRONLY, statfile.st_mode);
    
    char buffer[BUFFER_SIZE];

    //Write fd into fd1
    n = read(fd, buffer, statfile.st_size);
    int w = write(fd1 ,buffer, n);

    // Check that wrting happened correctly
    if (w == -1)
    {
       perror("Problem while writing encountered: ");
       // Error
       return 1;
    }
    
    //Closing files
    close(fd);
    close(fd1);

    return 0;
}
