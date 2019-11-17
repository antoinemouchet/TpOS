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

    // Open file where dico is stored in read only mode
    int fileDescriptor = open(DicoTextFilePath, O_RDONLY);

    if (fileDescriptor == -1)
    {
        perror("Error trying to load dictionary from file");
    }
    

} 

int main(int argc, char const *argv[])
{
    Dict *dictionary = NewDict();

    return 0;
}
