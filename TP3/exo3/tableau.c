#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void remove_word(char *text_pointer, int nb_words_to_dell)
{
    int word_to_dell;
    printf("Insert the index of the word to dell.\n>>> ");
    scanf("%d", &word_to_dell);
    //Loop until all strings after string deleted are moved
    for ( int i = word_to_dell; i < SIZE; i++)
    {
        strcpy((*text_pointer + i), (*text_pointer + i + 1));
    }
}


int main(int argc, char const *argv[])
{
    //Initialize an array of 50 strings each of 20 char max.
    char text[SIZE][20];

    //Initialize an array for a word of 20char max
    char word[20];

    //initialize the index of the word in array of word
    int text_ind = 0;
    //Initialize the amount of words to delete
    int nb_words = 0;

    //initialize a boolean
    int writing = 1;

    //Loop until user is done adding words
    while (writing)
    {
        //Get string from user
        printf("Insert a word (and press enter):\n>>> ");
        scanf("%[^\n]%*c", word);

        //Check if array is not full
        if (text_ind < SIZE)
        {
            //Add word in array
            strcpy(text[text_ind], word);
            //Increment index of array
            text_ind ++;
        }
        else
        {
            //Get info from user
            printf("No place left in the array, %s couldn't be inserted.\nInsert numbers of words to delete or 100 to stop writing:\n>>> ", word);
            scanf("%d", &nb_words);

            //Do nothing if 100 is entered
            if (nb_words == 100)
            {}

            //Make sure index of word is in array
            else if (nb_words < SIZE)
            {
                //initialize pointer on text
                char *pa = *text;

                //Loop until all strings after string deleted are moved
                for ( int i = 0; i < nb_words; i++)
                {
                    remove_word(*pa, nb_words);
                }
                //Add last word entered at the queue
                strcpy(text[strlen(*text)], word);
            }

            //number invalid
            else
            {
                printf("Number entered is unvalid.");
            }

            //Stop writing since array is full
            writing = 0;

        } 
    }

    //Display array
    printf("Array is:\n>>>");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%s ", text[i]);
    }

    return 0;

}
