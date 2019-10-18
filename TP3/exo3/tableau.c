#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5


int main(int argc, char const *argv[])
{
    //Initialize an array of 50 strings each of 20 char max.
    char text[SIZE][20];

    //Initialize an array for a word of 20char max
    char word[20];

    //initialize the index of the word in array of word
    int text_ind = 0;
    //Initialize the index of the word to delete
    int word_to_dell = 0;

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
            printf("No place left in the array.\nInsert index of word to delete or 100 to stop writing:\n>>> ");
            scanf("%d", word_to_dell);

            //stop writing
            if (word_to_dell == 100)
            {
                writing = 0;
            }

            //Make sure index of word is in array
            else if (word_to_dell < SIZE)
            {
                //Loop until all strings after string deleted are moved
                for ( int i = word_to_dell; i < SIZE; i++)
                {
                    strcpy(text[i], text[i + 1]);
                }
                //Add last word entered at the end
                strcpy(word, text[text_ind - 1]);
            }

            //number invalid
            else
            {
                printf("Number entered is unvalid.");
                writing = 0;
            }

        } 
    }

    return 0;

}
