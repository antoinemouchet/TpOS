#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 

#define BUF_SIZE 1024

void PrintCharInfFile(int fileDescriptor, int number, char *filename)
{
    
    char buffer[BUF_SIZE];
    
    // Get stats from original file
    struct stat statfile;
    stat(filename, &statfile);

    // Read whole file
    read(fileDescriptor, buffer, number);

    // Display appropriate number of byte
    write(1, buffer, number);
}


int main(int argc, char const *argv[])
{

    int son;

    if (argc != 2)
    {
        // Error case
        printf("argument error. 1 file waited");
        return 1;
    }

    // Create son
    son = fork();

    // Open file
    int fileDescriptor = open(argv[1], O_RDONLY);
    // Check error
    if (fileDescriptor == -1)
    {
        perror("Error encountered: ");
        return 1; 
    }

    switch (son)
    {
    case -1:
        perror("fork");
        return EXIT_FAILURE;
    
    //son case

    case 0:
        PrintCharInfFile(fileDescriptor ,5, argv[1]);
        break;
    //father case
    default:
        PrintCharInfFile(fileDescriptor, 10, argv[1]);
        break;
    }
    close(fileDescriptor);
    return 0;
}

