
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define SIZE_WORD 20

void remove_word(char text[][SIZE_WORD])
{
    int word_to_dell;

    printf("Insert the index of the word to dell.\n>>> ");
    scanf("%d", &word_to_dell);

    //Loop until all strings after string deleted are moved
    for ( int i = word_to_dell; i <= SIZE - 1; i++)
    {
        if (i != SIZE-1)
        {
            strcpy(text[i], text[i + 1]);
        }
        else
        {
            strcpy(text[i], "");
        }

    }
}

void DisplayArray(char text[][SIZE_WORD])
{
    printf("\nArray is: ");
    for (int j = 0; j < SIZE; j++)
        {
            printf("%s ", text[j]);
        }
}

int main(int argc, char const *argv[])
{
    //Initialize an array of SIZE strings each of SIZE_WORD char max.
    char text[SIZE][SIZE_WORD];

    //Initialize an array for a word of 20char max
    char word[SIZE_WORD];

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
        scanf("%s", word);

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
            //Make sure index of word is in array
            if (nb_words != 100 && nb_words >= 0 && nb_words < SIZE )
            {
                //Loop until all strings after string deleted are moved
                for ( int i = 0; i < nb_words; i++)
                {
                    remove_word(text);
                    //tab updated with nbwords less

                    //Display array when there is at least another word to remove
                    if (i < nb_words - 1)
                    {
                        DisplayArray(text);
                    }
                }

                //Add last word entered at the queue
                strcpy(text[SIZE - nb_words], word);
            }

            //number invalid
            else
            {
                printf("Number entered is invalid.");
            }

            //Stop writing since array is full
            writing = 0;

        }
    }

    //Display array
    DisplayArray(text);


    return 0;

}
