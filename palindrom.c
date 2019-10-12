#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

int is_palindrom(char string[])
{
    int low_ind, high_ind;

    //Initialize indexes
    low_ind = 0;
    high_ind = strlen(string) - 1;

    /* Loop until:
    - a difference is found
    - all letters are tested */
    while (high_ind > 1)
    {
        //If letters are different then return false
        if (string[low_ind] != string[high_ind])
        {
           return 0;
        }
        //Decrease high index and increase low index
        high_ind -= 1;
        low_ind += 1;
    }

    //string is a palindrom
    return 1; 
}

int main(int argc, char const *argv[])
{
    char sentence[MAX];
    int palindrom;
    //Get sentence from user
    printf("Insert a word (and press enter):\n>>> ");
    scanf("%[^\n]%*c", sentence);

    palindrom = is_palindrom(sentence);

    if (palindrom)
    {
        printf("%s is a palindrome.\n", sentence);
    }
    else
    {
        printf("%s is not a palindrome.\n", sentence);
    }

    scanf("%d", &palindrom);
    return 0;
}
