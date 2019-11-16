#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define charListSize 1024

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
        // Initialize list of characters sent and received
        char charList[charListSize], finalCharList[charListSize];
        // Variable to get inserted character
        char character;

       // Position counter
        int i = 0;

        // Read until end of line
        // 0 is standard input (keyboard)
       while(read(0, &character, 1) != 0)
        {
            charList[i] = character;
            i++;
            printf("%s", charList);
        }
        // Send data
        // Writing end of pipe is at 1 in the array
        write(fdPipe[1], charList, strlen(charList));

        // Close writing end of pipe now that we sent data
        close(fdPipe[1]);

        // Read data from child
        read(fdPipe[0], finalCharList, charListSize);

        // Close reading end of parent
        close(fdPipe[0]);

        // Display result
        printf("Sting entered was %s.\nFinal string is: %s.\n", charList, finalCharList);
    }
    // Child process
    else
    {
        /* The child inherited the same pipe as the parent process
        except that both ends are still open for the child.*/

        // Initialize array for data to receive
        char charListReceived[charListSize];
        // Read data from pipe and store it into array received
        read(fdPipe[0], charListReceived, charListSize);
        // Terminate string
        charListReceived[strlen(charListReceived)] = '\0';

        // Close reading end of son pipe
        close(fdPipe[0]);

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

            /* Method 3
            If we take a look at the ASCII table we realise that each upper case value
            is 32 (in decimal) less than the lower case. So something like

            charListReceived[j] = charListReceived[j] - 32;

            should work.
            */

            /* NOTE
            If we want to be able to remove non-classical alphabetical letter
            from being set to uppercase we can use an alphabet variable and
            check if character is in the string using strchr, making it upper case
            only if the return value was different from NULL;

            char alphabet[26] = "abcefghijklmnopqrstuvwxyz";
            char *returnValue;

            returnValue = strchr(alphabet, charListReceived[j])

            if (returnValue != NULL)
            {
                // MAKE UPPER CASE
            }
            */
        }
        // Send data back to parent process
        write(fdPipe[1], charListReceived, strlen(charListReceived));

        // Close writing end of son pipe
        close(fdPipe[1]);

    }

    return 0;
}
