#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_length(char word[])
{
    int index_1 = 0, length = 0;

    while (word[index_1] != '\0')
    {
        length += 1;

        index_1 ++;
    }
    
    return length;
}

int main(int argc, char const *argv[])
{
    int size;
    char sentence[50];

    printf("Insert a word (and press enter):\n>>> ");
    scanf("%[^\n]%*c", sentence);

    size = get_length(sentence);
    printf("This string is %d characters long.\n", size);
    
    return 0;
}

