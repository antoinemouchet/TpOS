#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char word[200];
    int n;

    //Get word from user
    printf("Insert a word.\n>>> ");
    scanf("%s", word);

    //Generate a new child
    n = fork();

    if (n < 0)
    {
        printf("There was an error generating the new process.");
    }
    
    return 0;
}
