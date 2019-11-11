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
    char sentence[number + 1];
    char buffer[BUF_SIZE];
    int nbread;
    
    // Get stats from original file
    struct stat statfile;
    stat(filename, &statfile);

    // Read whole file
    nbread = read(fileDescriptor, buffer, statfile.st_size);

    int i;
    // Adding char to the sentence (5 if father, 10 if son)
    // Make sure you don't add anymore characters if there is None to add anymore
    for (i = 0; i < number && i < nbread; i++)
    {
        // Move pointer to get next character
        sentence[i] = (char) getc(filename + i);
    }
    // Add EOF char
    sentence[i+1]='\0';

    // Display final sentence
    printf("%s", sentence);
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

    char* file = argv[1];
    // Create son
    son = fork();

    // Open file
    int fileDescriptor = open(file, O_RDONLY);
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
        PrintCharInfFile(fileDescriptor ,5, file);
        break;
    //father case
    default:
        PrintCharInfFile(fileDescriptor, 10, file);
        break;
    }
    close(fileDescriptor);
    return 0;
}

