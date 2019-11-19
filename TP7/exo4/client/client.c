#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define BUF_SIZE 1024

#define SEND_REQ "../tmp/sgbd_request"
#define GET_RES "../tmp/sgbd_result"


int main(int argc, char const *argv[])
{   

    int requestPipe, resultPipe, requestTag;

    // Open pipes
    requestPipe = open(SEND_REQ, O_WRONLY);
    resultPipe = open(GET_RES, O_RDONLY);
    // Check if it reached the server
    // Means that pipes were opened by server.
    if ((requestPipe == -1) || (resultPipe == -1))
    {
        printf("Couldn't reach the server\n");
        return 1;
    }
    printf("Server has been reached\n");
    // Start request
    do
    {
        // Reset each variable
        char word[128] = "";
        char definition[512] = "";
        char requestSentence[1024] = "";
        char resultSentence[1024] = "";

        // ASK A REQUEST
        printf("Choose one request:\n 0. Add a word + definition\n 1. Remove a word \n 2. Select a word from dict\n 3. Exit\n >");
        scanf("%d", &requestTag);
        // Get the newline char to avoid any problem
        getchar();
        switch (requestTag)
        {
            // Add a word
            case 0:
                printf("\nYou choose to add a word in the dict.\n");
                // Choose a word
                printf("Write a word: ");
                scanf("%[^\n]s", word);
                // Catch newline char
                getchar();
                // Choose his definition
                printf("Write its definition: ");
                scanf("%[^\n]s", definition);
                // Catch newline character
                getchar();

                // Init to send word and definition and adding tag in the pipe
                // RequestSentence is written Tag:size of word:size of definition:word:definition
                sprintf(requestSentence, "%d:%d:%d:%s:%s", requestTag, strlen(word), strlen(definition), word, definition);
                printf("\nRequest sent\n");
                break;

            // Remove a word from dict
            case 1:
                printf("\nYou choose to remove a word from dict.\n");
                printf("choose a word to delete: ");
                scanf("%[^\n]s", word);
                // Catch newline character
                getchar();

                // Init to send the word to delete and deleting tag in the pipe
                sprintf(requestSentence, "%d:%d:%s", requestTag,strlen(word), word);
                printf("\nRequest sent\n");
                break;

            // Select a word from dict
            case 2:
                printf("\nYou choose to select a word from dict.\n");
                printf("Which word do you want to know ? ");
                scanf("%[^\n]s", word);
                // Catch newline character
                getchar();
                // Init to send the word to find and finding tag in the pipe
                sprintf(requestSentence, "%d:%d:%s", requestTag, strlen(word), word);
                printf("\nRequest sent\n");
                break;

            // Leaving process
            case 3:
                printf("\nYou choose to exit\n");
                sprintf(requestSentence, "%d", requestTag);
                break;
            
            default:
                printf("\nInvalid choice, leaving.\n");
                sprintf(requestSentence, "%d", requestTag);
                break;
        }
        printf("%s\n", requestSentence);
        // Send requestSentence in the pipe 
        write(requestPipe, requestSentence, strlen(requestSentence));
        

        // RECEIVE RESULT 
        // Don't wait for a result if  requestTag >=3
        if(requestTag < 3)
        {
            read(resultPipe, resultSentence, BUF_SIZE);
            printf("%s\n", resultSentence);
        }
        
    } while (requestTag < 3);
    // Closing pipe
    close(resultPipe);
    close(requestPipe);
    return 0;
}
