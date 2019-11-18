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

void saveDictionary(Dict* DictionaryName)
{
    // Initialize element of dict
    DictElement* element;

    // Element of dictionary is the first
    element = DictionaryName->head;

    // Open file in which we will store the dictionary
    // Open in Write only if already exists, create it otherwise
    // If created give user read and write permission on file
    int dictFileDescriptor = open(DICT_PATH, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    if (dictFileDescriptor == -1)
    {
        perror("Problem opening dico file");
        return 1;
    }

    // Loop to get all elements of dict
    while (element != NULL)
    {
        // Get info about word
        char word[] = element->word;
        char definition[] = element->definition;

        // Write word and its definition into file with format
        // WORD
        // DEFINITION
        write(dictFileDescriptor, word, strlen(word));
        write(dictFileDescriptor, '\n', 1);
        write(dictFileDescriptor, definition, strlen(definition));
        write(dictFileDescriptor, '\n', 1);

        // Move pointer to next element in dictionary
        element = element->next;
    }

    // Close the file after storing whole dictionary
    close(dictFileDescriptor);
}

int main(int argc, char const *argv[])
{
    // Initialize a dictionary in which we will store data
    Dict *dictionary;

    // Initialize reset of dict value
    int reset = 0;

    // Initialize counter
    int i = 0;

    // Display that server is starting
    printf("Starting the server.\n");

    // CREATE NAMED PIPES
    // Pipe to get request
    int pipeReqReturn = mkfifo(GET_REQ, 0666);
    // Check that pipe was created correctly
    if (pipeReqReturn == -1)
    {
        perror("Error creating pipe to get request");
        return 1;
    }

    // Pipe to send result
    int pipeSendReturn = mkfifo(SEND_RES, 0666);
    // Check that pipe was created correctly
    if (pipeSendReturn == -1)
    {
        perror("Error creating pipe to send result");
        return 1;
    }

    // CHECK IF WE RESET DICTIONARY
    // Loop until we tested all arguments or we found the reset arg
    while (i < argc && !reset)
    {
        // Return 0 if same string
        int isReset = strcmp(argv[i], "-i");
        // Check if we reset
        if (isReset == 0)
        {
            // Update reset value to leave loop
            reset = 1;
        }
        // Update counter variable
        i++; 
    }
    // Reset dictionary by creating a new one
    if (reset)
    {
        // Display reset message
        printf("Argument -i was inserted, dictionary has been resetted.\n");
        dictionary = NewDict();
    }
    // Get dictionary from file
    else
    {
        dictionary = loadDictionary(DICT_PATH);
    }

    // OPEN NAMED PIPES
    // Get request so read only
    int pipeReqDescriptor = open(GET_REQ, O_RDONLY);

    // Check it opened correctly
    if (pipeReqDescriptor == -1)
    {
        perror("Error opening named pipe to get request");
        return 1;
    }
    
    // Send result so write only
    int pipeSendDescriptor = open(SEND_RES, O_WRONLY);

    // Check it opened correctly
    if (pipeSendDescriptor == -1)
    {
        perror("Error opening named pipe to send result");
        return 1;
    }

    // DO REQUEST
    // Initialize array of char where request will be stored
    char request[BUF_SIZE];
    // Initialize code which will define what's the request to do
    int code;

    // Initialize array of char to store word and its definition
    char wordReq[BUF_SIZE], definitionReq[BUF_SIZE];

    // Initialize array of char for the result to be sent
    char result[BUF_SIZE];

    // Loop until we get the request to close
    do
    {
        // Get request
        read(pipeReqDescriptor, request, BUF_SIZE);
        // Get code using sscanf to extract the only int in the string
        sscanf(request, "%d", &code);
        // Display request received
        printf("Request received: %s\n", request);

        switch (code)
        {
            // Add word in dictionary
            case 0:
                // Get actual word and its definition from request
                sscanf(request,"%d %s %s",&code, wordReq, definitionReq);
                // Add element into dictionary
                AddElement(dictionary, wordReq, definitionReq);

                // Display that it worked
                printf("%s was added into the dictionary.\n", wordReq);
                // Send result of request
                sprintf(result, "ADD OK");
                write(pipeSendDescriptor, result, strlen(result) + 1);
                break;
            
            // Remove word from dictionary
            case 1:
                // Get word from request
                sscanf(request, "%d %s", &code, wordReq);

                // Check that word is in dict
                if (Search(dictionary, wordReq) == -1)
                {
                    printf("Word not in dict.\n");
                    // Send result of request
                    sprintf(result, "REMOVE FAILED (%s not in dict)", wordReq);
                    write(pipeSendDescriptor, result, strlen(result));
                }
                // Word in dict so remove it
                else
                {
                    // Remove word from dict
                    RemoveWord(dictionary, wordReq);
                    
                    // Display that it worked
                    printf("%s was removed from dictionary.\n");
                    // Send result of request
                    sprintf(result, "REMOVE OK");
                    write(pipeSendDescriptor, result, strlen(result) + 1);
                }
                break;
            // Display word
            case 2:
                // Get word from request
                sscanf(request, "%d %s", &code, wordReq);

                int index = Search(dictionary, wordReq);
                // Check that word is in dict
                if (index == -1)
                {
                    printf("Word not in dict.\n");
                    // Send result of request
                    sprintf(result, "SEARCH FAILED (%s not in dict)", wordReq);
                    write(pipeSendDescriptor, result, strlen(result));
                }
                // Word in dict so display it and return its index
                else
                {
                    // Display word from dict
                    displayWord(dictionary, wordReq);
                    
                    // Display that it worked
                    printf("%s was displayed from dictionary.\n");
                    // Send result of request
                    sprintf(result, "SEARCH OK (word at index: %d) ~ Check server for more info about word.", index);
                    write(pipeSendDescriptor, result, strlen(result) + 1);
                }
                break;
        }
    }while(code < 3);

    // Display that we're shutting down the server
    printf("Stopping the server\n");

    // Close named pipes
    close(pipeReqDescriptor);
    close(pipeSendDescriptor);

    // Remove named pipes
    unlink(GET_REQ);
    unlink(SEND_RES);

    // Save dictionary into file
    saveDictionary(dictionary);

    // Remove dictionary
    DelDict(dictionary);

    return 0;
}
