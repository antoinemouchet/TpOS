#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int AllVowels(char *word)
{
    /*Initialize string of vowels.
    vowels are sorted in ascending order of frequency apparition
    (average of apparition in French and English)*/
    char* vowels = "uoiae";

    //Loop to see if all vowels are in word
    for (int PosCheck = 0; PosCheck < 5; PosCheck++)
    {
        //If one vowel is not in the word then return false
        if (strchr(word, vowels[PosCheck]) == NULL)
        {
            return 0;
        }
    }
    /*If loop is completed without returning 0 
    It means each vowel was found at a point so it's true. */
    return 1;
}

int main(int argc, char const *argv[])
{
    //Initialize word and result value of checking
    char word[200];
    int n, inString = 0;

    //Get word from user
    printf("Insert a word.\n>>> ");
    scanf("%s", word);

    //Generate a new child
    n = fork();

    //Error case
    if (n < 0)
    {
        printf("There was an error generating the new process.");
    }
    /* Son case
    Check if all vowels are in the word and return the result to father process. */
    else if (n == 0)
    {
        return AllVowels(word);
    }
    // Father case
    else
    {
        //Wait for result
        wait(&inString);

        //All vowels are in string
        if (inString)
        {
            printf("All vowels are in %s.\n", word);
        }
        else
        {
            printf("%s does not contain all vowels", word);
        }
    }
    return 0;
}
