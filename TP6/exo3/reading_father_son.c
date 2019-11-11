#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 

#define BUF_SIZE 1024

void PrintCharInfFile(char *filePath, int number)
{
    int fileDescriptor = open(filePath, O_RDONLY);
    char sentence[number];
    char buffer[BUF_SIZE];
    int nbread;
    // Check error
    if (fileDescriptor == NULL)
    {
        return 1; 
    }
    // Get stats from original file
    struct stat statfile;
    stat(fileDescriptor, &statfile);

    // Read whole file
    nbread = read(fileDescriptor, buffer, statfile.st_size);

    // Adding char to the sentence (5 if father, 10 if son)
    // Make sure you don't add anymore characters if there is None to add anymore
    for (int i = 0; i < number && i < nbread; i++)
    {
        // Move pointer to get next character
        sentence[i] = getc(buffer + i);
    }

    // Display final sentence
    printf(sentence);
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

    switch (son)
    {
    case -1:
        perror("fork");
        return EXIT_FAILURE;
    
    //son case
    case 0:
        PrintCharInfFile(argv[1], 5);
        break;
    
    //father case
    default:
        PrintCharInfFile(argv[1], 10);
        break;
    }
    return 0;
}

