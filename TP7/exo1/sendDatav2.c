#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char const *argv[])
{
    char pipePath[] = "/tmp/fdPipe";
    int fdPipe;

    // Create pipe
    int pipeReturn = mkfifo(pipePath, 0666);

    // Check if there was an error creating pipe
    if (pipeReturn == -1)
    {
        // Display error and exit program
        perror("Error creating pipe");
        return 1;
    }

    // Create child process
    int forkReturn = fork();
    
    // Error case
    if (forkReturn < 0)
    {
        // Display error and exit program
        perror("Error creating process");
        return 1;
    }
    // Parent case
    else if (forkReturn > 0)
    {
        // Open file
        fdPipe = open(pipePath, O_WRONLY);

        // Initialize data to send
        char data[] = "je t'envoie des données";
        // Initialize nb of bytes sent by process
        int nbBytes = 0;

        // Send data
        nbBytes = write(fdPipe, data, strlen(data));

        // Close file
        close(fdPipe);

        // Display number of bytes sent and pid.
        printf("I'm the parent. My pid is: %d and I sent %d bytes.\n", getpid(), nbBytes);
    }
    // Child case
    else
    {
        // Initialize command to execute
        char command[256];
        // List of argument for command
        char arg[2][10];

        // Command name
        strcpy(arg[0], "od ");
        // Option
        strcpy(arg[1], "-c ");

     
        // Build command using format
        sprintf(command, "%s%s%s", arg[0], arg[1], pipePath);
        command[strlen(command)] = '\0';

        // Actually use command
        system(command);
    }

    unlink(pipePath);
    return 0;
}
