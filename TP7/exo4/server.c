#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dictHeader.h"

#define BUF_SIZE 1024

#define GET_REQ "/tmp/sgbd/request"
#define SEND_RES "/tmp/sgbd/result"

#define DICT_PATH "dict.txt"

Dict* loadDictionary(char* DicoTextFilePath)
{
    // Create dictionary to return
    Dict *dictionary = NewDict();

    // Initialize character as an array so that we can use it
    // To store the read character in the loop
    char character[1];
    
    // Initialize word and definition arrays
    char word[BUF_SIZE], definition[BUF_SIZE];

    // Counter variable
    int counter = 0;

    // define storage emplacement as the word
    char *reading = word;

    // Open file in which dico is stored in read only mode
    int fileDescriptor = open(DicoTextFilePath, O_RDONLY);

    // Problem opening file
    if (fileDescriptor == -1)
    {
        perror("Error trying to load dictionary from file");
        // Error quit function
        return 1;
    }
    // Store dico informations into a structure
    else
    {
        // Read letter by letter
        while (read(fileDescriptor, character, 1) == 1)
        {
            // Update reading by adding character read
            reading[counter] = *character;

            // Check if character is end of line
            if (*character == '\n')
            {
                // Terminate string properly
                reading[counter] = '\0';

                // One line is a word and the following is its definition
                if (reading == word) 
                {
                    // Change storage emplacement of the read input
                    reading = definition;
                }
                // Definition is now complete and so is the word
                else
                {
                    // Actually add element into dictionary
                    AddElement(dictionary, word, definition);
                    // Set the emplacement storage of read to word again
                    reading = word;
                }
                // Reset position counter to 0
                counter = 0;
            }
            // Not the end of line
            else
            {
                // Update position counter
                counter++;
            }
        }
    }
    // Close file containing dico
    close(fileDescriptor);

    // Return the dictionary
    return dictionary;
}

int main(int argc, char const *argv[])
{
    Dict *dictionary = NewDict();

    return 0;
}
