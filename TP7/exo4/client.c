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
        printf("choose one request:\n 0. Add a word + definition\n 1. Remove a word \n 2. Select a word from dict\n 3. Exit\n >");
        scanf("%d", &requestTag);
        switch (requestTag)
        {
            //Add a word
            case 0:
                printf("you choose to add a word in the dict.");
                break;
            //Remove a word from dict
            case 1:
                printf("you choose to remove a word from dict.");
                break;
            //select a word from dict
            case 2:
                printf("you choose to select a word from dict.");
                break;
            //leaving process
            case 3:
                printf("you choose to exit");
                break;
        }
    } while (requestTag < 3);
    
    return 0;
}
