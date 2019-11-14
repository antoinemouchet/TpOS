#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    // Array for pipe
    int fdPipe[2];

    // Create pipe
    int pipeReturn = pipe(fdPipe);

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
        // Initialize data to send
        char data[] = "je t'envoie des données";
        // Initialize nb of bytes sent by process
        int nbBytes = 0;

        // Close the reading end of the pipe for the parent
        // We want to send data not read some here
        close(fdPipe[0]);

        // Send data
        // Writing end of pipe is at 1 in the array
        nbBytes = write(fdPipe[1], data, strlen(data));

        // Close writing end of pipe now that we sent data
        close(fdPipe[1]);

        // Display number of bytes sent and pid.
        printf("I'm the parent. My pid is: %d and I sent %d bytes.\n", getpid(), nbBytes);
    }
    // Child case
    else
    {
        /* The child inherited the same pipe as the parent process
        except that both ends are still open for the child.*/

        // Initialize array for data to receive
        char received[500];
        // Initialize command to execute
        char command[256];
        // List of argument for command
        char arg[3][100];

        // Close writing end of pipe
        // Receiving data not sending
        close(fdPipe[1]);
        
        // Read data from pipe and store it into array received
        read(fdPipe[0], received, 500);

        // Close reading end of pipe 
        // Data was received
        close(fdPipe[0]);

        // Command name
        *arg[0] = "od ";
        // Option
        *arg[1] = "-c ";
        // Data
        *arg[2] = received;

        // Build command using format
        sprintf(command, "%s%s%s", arg[0], arg[1], arg[2]);

        // Actually use command
        system(command);
    }
    return 0;
}
