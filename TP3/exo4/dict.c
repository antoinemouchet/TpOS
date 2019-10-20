#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct DictElement
{
    //Word itself and its definition
    char* word;
    char* definition; 

    struct DictElement* next ;

} DictElement;

int isEmpty(DictElement* head)
{

    //Initialize current position of pointer
    struct DictElement *PosPoint = head;

    //If head is null then it's empty
    if (head == NULL)
    {
        return 1;
    }

    //Return 0 if dict is not empty
    return 0;
}

void NewHead(char* word, char* definition, DictElement** head)
{
    DictElement* NextEl;
    NextEl = (DictElement*) malloc (sizeof(DictElement));

    //Values of new element
    NextEl -> word = word;
    NextEl -> definition = definition;

    //Move head pointer
    NextEl -> next = *head;
    *head = NextEl;
 
}

void NewQueue(char* word, char* definition, DictElement** head)
{
   
    DictElement* NewEl = (DictElement*) malloc(sizeof(DictElement));
  
    DictElement *last = *head;  
   
    
    NewEl -> word  = word;
    NewEl -> definition = definition;
    NewEl -> next = NULL;
  
    //If list is empty then
    if (isEmpty(*head))
    {
        *head = NewEl;
    }
    else
    {
        //Loop to make it the last one
        while (last -> next != NULL)
        {
            last = last -> next;
        }
        
        last -> next = NewEl;
    }
}

void NewElement(int InsertInd, char* word, char* definition, DictElement** head)
{
    DictElement* PosPoint =  head;
    int pos = 0;

    //If inserted as first element then head
    if (InsertInd == 0)
    {
        NewHead(word, definition, head);
    }
    
    else
    {
        DictElement* NewEl = (DictElement*) malloc(sizeof(DictElement));
        NewEl -> word  = word;
        NewEl -> definition = definition;

        //Loop until at point of insertion
        while (PosPoint != NULL && pos != InsertInd - 1)
        {
            PosPoint = PosPoint -> next;
            InsertInd++;
        }
        //check if it's at last position
        if (PosPoint == NULL)
        {
            NewQueue(word, definition, head);
        }
        else
        {
            //Update pointers
            NewEl -> next = PosPoint -> next;
            PosPoint -> next = NewEl;
        }
    }
}

