#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 
 void PrintCharInfFile(char *filePath, number)
{
    int *file = open(filePath, O_RDONLY);
    char *sentence;
    size_t n = 0;
    int c;

    //check error
    if (file == NULL)
        return 1; 
    
    //initiate sentence
    sentence = malloc(1000);
    int i = 0;
    
    //adding char to the sentence (5 if father, 10 if son)
    while ((c = read(fd,buffer,50) && i != number)
    {
        sentence[n++] = (char) c;
    }

    printf(sentence);
}
int main(int argc, char const *argv[])
{
    int son;

    if (argc != 2)
    {
        //error case
        printf("argument error. 1 file waited");
        return 1;
    }
    //create son
    son = fork();

    switch (son)
    {
    case -1:
        perror("fork");
        return EXIT_FAILURE;
    
    //son case
    case 0:
        PrintCharInfFile(argc[1], 5);
        break;
    
    //father case
    default:
        PrintCharInfFile(argc[1], 10);
        break;
    }
    return 0;
}

