#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

#define SEND_REQ "/tmp/sgbd/request"
#define GET_RES "/tmp/sgbd/result"


int main(int argc, char const *argv[])
{   
    char word[128];
    char definition[512];
    char requestSentence[1024];
    char resultSentence[1024];
    int requestPipe, resultPipe, requestTag;
    requestPipe = open(SEND_REQ, O_WRONLY);
    resultPipe = open(GET_RES, O_RDONLY);
    // check if it reached the server
    if ((requestPipe == -1) || (resultPipe == -1))
    {
        printf("couldn't reach the server");
        return 1;
    }
    printf("server has been reached");
    //start request
    do
    {
        // ASK A REQUEST
        printf("choose one request:\n 0. Add a word + definition\n 1. Remove a word \n 2. Select a word from dict\n 3. Exit\n >");
        scanf("%d", &requestTag);
        switch (requestTag)
        {
            //Add a word
            case 0:
                printf("you choose to add a word in the dict.");
                //choose a word
                printf("write a word: ");
                scanf("%s", word);
                //choose his definition
                printf("write its definition: ");
                scanf("%s", definition);

                // Init to send word and definition and adding tag in the pipe
                // requestSentence is written Tag:word:its definition
                sprintf(requestSentence, "%d:%s:%s", &requestTag, word, definition);
                printf("Request send");
                break;

            //Remove a word from dict
            case 1:
                printf("you choose to remove a word from dict.");
                printf("choose a word to delete: ");
                scanf("%s", word);

                // Init to send the word to delete and deleting tag in the pipe
                sprintf(requestSentence, "%d:%s", &requestTag, word);
                printf("Request send");
                break;
            //select a word from dict
            case 2:
                printf("you choose to select a word from dict.");
                printf("Wich word want you to know ? ");
                scanf("%s", word);
                // Init to send the word to find and finding tag in the pipe
                sprintf(requestSentence, "%d:%s", &requestTag, word);
                printf("Request send");
                break;
            //leaving process
            case 3:
                printf("you choose to exit");
                break;
        }
        // Send requestSentence in the pipe 
        write(requestPipe, requestSentence, strlen(requestSentence));
        

        // RECIEVE RESULT 
        // Don't wait for a result if  requestTag >=3
        if(requestTag < 3)
        {
            read(resultPipe, resultSentence, BUF_SIZE);
            printf("%s", resultSentence);
        }
        
    } while (requestTag < 3);
    //closing pipe
    close(resultPipe);
    close(requestPipe);
    return 0;
}
