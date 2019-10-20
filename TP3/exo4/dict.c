#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dict_element
{
    //Word itself and its definition
    char word[100];
    char definition[500]; 

    struct dict_element *next ;

};

int isEmpty(struct dict_element* head)
{
    //Initialize nb of elements in struct
    int NbElements = 0;

    //Initialize current position of pointer
    struct dict_element *PosPoint = head;

    //Loop on the 
    while (PosPoint != NULL)
    {
        //Increment nb of elements and move pointer
        NbElements ++;
        PosPoint = PosPoint -> next;
    }

    /*Check if dict is empty
    Return a positive integrer if yes. */
    if (NbElements == 0)
    {
        return 1;
    }
    
    //Return 0 if dict is not empty
    return 0;
}