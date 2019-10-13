#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int get_length(char word[])
{
    int index = 0, length = 0;

    while (word[index] != '\0')
    {
        //increase length and index by 1
        length += 1;

        index ++;
    }
    
    return length;
}

int get_freq_letter(char word[], char letter)
{
    int word_len, index = 0, nb_occ = 0;
    //Get length of string
    word_len = strlen(word);

    //Loop on every character of string
    for (index; index < word_len; index++)
    {
        //Check if character is the letter
        if (tolower(word[index]) == letter)
        {
           nb_occ ++; 
        } 

    }
    
    return nb_occ;
}

int main(int argc, char const *argv[])
{
    int size, letter_occ[26], letter_index;
    char sentence[50], alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

    //Get string from user
    printf("Insert a word (and press enter):\n>>> ");
    scanf("%[^\n]%*c", sentence);

    //get size of string
    size = get_length(sentence);
    //Display length of string
    printf("This string is %d characters long.\n", size);

    //Initialize index at 0
    letter_index = 0;

    //Loop on every letter of the alphabet
    for (letter_index; letter_index < 27; letter_index++)
    {
        letter_occ[letter_index] = get_freq_letter(sentence, alphabet[letter_index]);
        //Display number of times each letter appears
        printf("%c appears %d times in %s.\n", alphabet[letter_index], letter_occ[letter_index], sentence);
    }

    return 0;
}

