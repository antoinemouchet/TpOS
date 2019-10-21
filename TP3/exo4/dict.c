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
            printf("Word found at index: %d.\n", count);
            return count;
        }
        //Move pointer and increments counter
        PosPoint = PosPoint->next;
        count ++;
    }

    printf("Word not found.\n");
    return -1;
}

void RemoveWord(char* word, DictElement** head)
{
    int WordIndex = Search(*head, word);
    //Check that word was found
    if (WordIndex != -1)
    {
        RemoveElement(WordIndex, head);
    }  
}

void DisplayMenu(DictElement** head)
{
    int choice;
    int index = 0;
    char word[100], definition[200];
    printf(" 0. Exit\n"
           " 1. Insert an item at index\n"
           " 2. Insert new head\n"
           " 3. Insert at the end of the queue\n"
           " 4. Remove item at index\n"
           " 5. Remove head\n"
           " 6. Remove queue\n"
           " 7. Remove a word\n"
           " 8. Search word\n"
           " 9. Sort list in ascending order\n"
           " 10. Sort list in descending order\n"
           " 11. Display words by pages of 10\n"
           ">>> ");
    
    scanf("%d", &choice);
  
    switch (choice) 
    {
        //item at index
        case 1:
            //Get index
            printf("Index\n>>> ");
            scanf("%d", &index);

            //Get word
            printf("Word\n>>> ");
            scanf("%s", word);

            //Get definition
            printf("Definition\n>>> ");
            scanf("%s", definition);

            NewElement(index, word, definition, head);
        break;
        
        //New head
        case 2:
            //Get word
            printf("Word\n>>> ");
            scanf("%s", word);
            //get definition
            printf("Definition\n>>> ");
            scanf("%s", definition);

            NewHead(word, definition, head);
            break;
        
        //New queue
        case 3:
            //Get word
            printf("Word\n>>> ");
            scanf("%s", word);
            //get definition
            printf("Definition\n>>> ");
            scanf("%s", definition);

            NewQueue(word, definition, head);
            break;
        //Remove item at index
        case 4:
            //get index
            printf("Index\n>>> ");
            scanf("%d", &index);

            RemoveElement(index, head);
            break;
        
        //Remove head
        case 5:
            RemoveHead(head);
            break;

        //Remove Queue
        case 6:
            RemoveQueue(head);
            break;

        //Remove specific word
        case 7:
            //Get word to delete
            printf("Word\n>>> ");
            scanf("%s", word);

            RemoveWord(word, head);
            break;

        //Search word
        case 8:
            //Get word to search for
            printf("Word\n>>> ");
            scanf("%s", word);

            printf("The index of %s is\n>>>  %d", word, Search(*head, word));
            break;

        //Sort in ascending order
        case 9:
            break;

        //Sort in descending order
        case 10:
            break;
        
        //Display dictionary by pages of 10 words
        case 11:
            break;
    
        default:
            return;
    }
    printf("\n");
}

DictElement* CopyDict(DictElement* head)
{
    //head of dict to copy
    DictElement* PosPoint = head;
    //Head of new dict
    DictElement* NewDict = NULL;

    //Loop on the whole list
    while (PosPoint != NULL)
    {
        //Copy element in new dict by adding it at last position
       NewQueue(PosPoint->word, PosPoint->definition, &NewDict);
       PosPoint = PosPoint->next;
    }
    //Return
    return NewDict;
}

//Main function
int main(int argc, char const *argv[])
{
    //Initialize array
    DictElement * head, *copy;

    head = (DictElement *) malloc(sizeof(DictElement));
    (*head).word = "test";
    (*head).definition = "Ceci est un test";
    (*head).next = NULL;

    NewQueue("test2", "Wow un deuxieme test", &head);
    RemoveHead(&head);
    Search(head, "test2");
    DisplayMenu(&head);
    copy = (DictElement *) malloc(sizeof(DictElement));
    copy = CopyDict(head);

    return 0;
}