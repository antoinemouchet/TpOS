#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/wait.h>

#define charListSize 1024

int main(int argc, char const *argv[])
{
    // Array for pipes
    int fdPipeSending[2], fdPipeReturning[2];

    // Create pipes
    int pipeReturn1 = pipe(fdPipeSending);
    int pipeReturn2 = pipe(fdPipeReturning);

    // Check if there was an error creating pipe
    if (pipeReturn1 == -1 || pipeReturn2 == -1)
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
        // Close reading end of sending pipe
        close(fdPipeSending[0]);
        // Close writing end of returning pipe
        close(fdPipeReturning[1]);

        // Initialize list of characters sent and received
        char charList[charListSize], finalCharList[charListSize];
        
        // Get sentence
        write(1, "Insert some characters (press enter after your last character):\n>>> ", 69);
        // 0 is standard input (keyboard)
        read(0, charList, charListSize);

        // Send data
        // Writing end of pipe is at 1 in the array
        write(fdPipeSending[1], charList, strlen(charList) - 1);

        // Close writing end of pipe now that we sent data
        close(fdPipeSending[1]);

        // Wait for child to do its job
        wait(NULL);

        // Read data from child
       int nbBytes = read(fdPipeReturning[0], finalCharList, charListSize);

        // Close reading end of parent
        close(fdPipeReturning[0]);

        // Display result (1 is standard output)
        write(1, finalCharList, nbBytes);
    }
    // Child process
    else
    {
        /* The child inherited the same pipes as the parent process
        except that both ends are still open for the child.*/

        // Close writing end of pipe from which data was sent in parent process
        close(fdPipeSending[1]);
        // Close reading end of pipe with which we return updated char
        close(fdPipeReturning[0]);

        // Initialize array for data to receive
        char charListReceived[charListSize];
        // Read data from pipe and store it into array received
        read(fdPipeSending[0], charListReceived, charListSize);

        // Close reading end of son pipe
        close(fdPipeSending[0]);

        // Make every character of the list upper case
        for (int j = 0; j < strlen(charListReceived) - 1; j++)
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

            /* Method 3
            If we take a look at the ASCII table we realise that each upper case value
            is 32 (in decimal) less than the lower case. So something like the code below 
            should work

            charListReceived[j] = charListReceived[j] - 32;            
            */

            /* NOTE
            If we want to be able to remove non-classical alphabetical letter
            from being set to uppercase we can use an alphabet variable and
            check if character is in the string using strchr, making it upper case
            only if the return value was different from NULL;

            char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
            char *returnValue;

            returnValue = strchr(alphabet, charListReceived[j]);

            if (returnValue != NULL)
            {
                // MAKE UPPER CASE
            }
            */
        }
        // Send data back to parent process
        write(fdPipeReturning[1], charListReceived, strlen(charListReceived) - 1);

        // Close writing end of son pipe
        close(fdPipeReturning[1]);
        // Exit child
        exit(0);
    }

    return 0;
}
