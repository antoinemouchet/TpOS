#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    //Check that 2 arguments were given (string and substring)
    if (argc != 3)
    {
        printf("You did not give a proper amount of arguments.");
        //Return 1 to show there was an error
        return 1;
    }

    //Get string and substring to look for
    const char *sentence = argv[2];
    const char *substring = argv[1];

    //Get len of sentence and substring
    int str_len = strlen(sentence), sub_len = strlen(substring);

    //Make sure that substring is smaller than sentence
    if (str_len < sub_len)
    {
        printf("The substring is bigger than the string.");
        //Return 1 to show there was an error
        return 1;
    }
    /*indexes of substring:
    -index of letter we are looking at
    -index of starting 
    -index of end */
    int sub_ind = 0, start_sub = 0, end_sub = 0;
    
    //letter index and substring not found
    int letter_ind = 0, sub_found = 0;

    //Loop until sentence is analyzed or substring is found
    while (letter_ind < str_len && sub_found == 0)
    {
        //Check if letter in string corresponds to letter substring
        if (sentence[letter_ind] == substring[sub_ind])
        {
            //Check if we already have the index where the substring starts
            if (start_sub < 0)
            {
                //Set the index of first letter of substring
                start_sub = letter_ind;
            }

            //Check if whole word is found
            if (sub_ind == (sub_len -1))
            {
                end_sub = start_sub + (sub_len - 1);
                sub_found = 1;
            }

            //Check next letter of substring
            sub_ind ++;
        }

        //Reset if letters from sentence are different from substring
        else
        {
            start_sub = -1;
            sub_ind = 0;
        }

        letter_ind ++;
    }

    //Check if substring was found
    if (start_sub >= 0 && end_sub >= start_sub)
    {
        printf("%s is a substring of %s\nStarting index: %d\nEnding index: %d", substring, sentence, start_sub, end_sub);
    }
    else
    {
        printf("%s was not found in %s", substring, sentence);
    }

    return 0;
}
