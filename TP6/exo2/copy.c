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
    // Check that the good amount of arguments was given.
    if (argc != 3)
    {
        printf("Wrong amount of arguments. 2 doc names waited.\n");
        // Error case
        return 1;
    }

    // Get names of files from the arguments passed in the command line.
    char fileName1[] = argv[1];
    char fileName2[] = argv[2];


    return 0;
}
