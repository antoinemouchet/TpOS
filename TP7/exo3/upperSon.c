#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

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

    // Initialize list of characters sent
    char charList[1024];
    // Variable to get inserted character
    char character;
    

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
        // Initialize nb of bytes sent by process
        int nbBytes = 0;

       // Position counter
        int i = 0;

        // Read until end of line
        // 0 is standard input (keyboard)
       while(read(0, &character, 1) > 0)
        {
            charList[i] = character;
            i++;
        }

        // Send data
        // Writing end of pipe is at 1 in the array
        nbBytes = write(fdPipe[1], charList, strlen(charList));

        // Close writing end of pipe now that we sent data
        close(fdPipe[1]);

    }
    else
    {
        /* The child inherited the same pipe as the parent process
        except that both ends are still open for the child.*/

        // Initialize array for data to receive
        char charListReceived[1024];
        // Read data from pipe and store it into array received
        read(fdPipe[0], charListReceived, 1024);
        // Terminate string
        charListReceived[strlen(charListReceived)] = '\0';

        // Make every character of the list upper case
        for (int j = 0; j < strlen(charListReceived); j++)
        {
            // Method 1 using toupper defined in ctype.h
            charListReceived[j] = toupper(charListReceived[j]);

            /* Method 2
            We can use a case - switch statement to check each letter
            and make it upper case by just writing it, it would look like
            
            switch(charListReceived[j])
            {
                case 'a':
                    charListReceived[j] = 'A';
                    break;
            }
            
            */

           
        }
        

    return 0;
}
