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
  
    DictElement *PosPoint = *head;
   
    
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
        while (PosPoint -> next != NULL)
        {
            PosPoint = PosPoint -> next;
        }
        
        PosPoint -> next = NewEl;
    }
}

void NewElement(int InsertInd, char* word, char* definition, DictElement** head)
{
    DictElement* PosPoint = *head;
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

void RemoveElement(int index, DictElement** head)
{
    if (index < 0)
    {
       printf("Index is invalid.\n");
    }
    
   // If linked list is empty 
   else if (isEmpty(*head)) 
    {
        printf("There is nothing to delete.\n");
    }

    else
    {

        //Get actual head in case we need to delete it
        DictElement* tmp = *head; 
        
        // If head needs to be removed 
        if (index == 0) 
        { 
            //New head is second element
            *head = tmp -> next; 
            //free space used
            free(tmp); 
        }

        else
        {
            //Initialize counter
            int i = 0;
            //Loop until element before element to delete is reached
            while (i < index - 1 && tmp != NULL)
            {   
                //Get next element
                tmp = tmp -> next;

                //Increment counter
                i++;
            }

            //index can not be found
            if (tmp == NULL)
            {
                printf("index is out of bounds.\n");
            }

            //index was reached
            else
            {
                DictElement* NewNext = tmp -> next -> next;
                //remove it from memory
                free(tmp->next);
                //Adapt pointers
                tmp -> next = NewNext;
            }   
        }
    }
} 


void RemoveHead(DictElement** head)
{
    RemoveElement(0, head);
}

int GetSize(DictElement* head)
{
    //Basic case
    if (isEmpty(head))
    {
        return 0;
    }

    //Recursive Case
    return 1 + GetSize(head -> next);
}

void RemoveQueue(DictElement** head)
{
    int lastInd = GetSize(*head) - 1;
    RemoveElement(lastInd, head);
}


void RemoveWord(DictElement** head, char* word)
{
    int WordIndex = Search(head, word);
    //Check that word was found
    if (WordIndex != -1)
    {
        RemoveElement(WordIndex, head);
    }  
}

int Search(DictElement* head, char* word) 
{ 
    DictElement* PosPoint = head;
    int count = 0;
    //Loop until element is found, return index of element 
    while (PosPoint != NULL) 
    { 
        //Check if words matched
        if (PosPoint->word == word)
        {
            printf("Word found at index: %d", count);
            return count;
        }
        //Move pointer and increments counter
        PosPoint = PosPoint->next;
        count ++;
    }

    printf("Word not found.");
    return -1;
}

int main(int argc, char const *argv[])
{
    DictElement * head, * next;
    // allocation dynamique
    head = (DictElement *) malloc(sizeof(DictElement));
    (*head).word = "test";
    (*head).definition = "Ceci est un test";
    (*head).next = NULL;
    (*head).next = (DictElement *) malloc(sizeof(DictElement));
    next = (*head).next;

    Search(head, "test");
    
    return 0;
}

