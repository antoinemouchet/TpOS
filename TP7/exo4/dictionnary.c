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

typedef struct Dictionary
{
    // Size of dictionary
    int size;
    struct DictElement *head;

} Dict;
/*
// UPDATED
int isEmpty(Dict *dict)
{
    // Check if size of dict is 0
    if (dict->size == 0)
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

    //definitions of new element
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

    //If inserted as head element then head
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

void DisplayDictByTen(DictElement* head)
{
    int CountEl = 0, CountPage = 0, choice = 0;

    //Make sure there is at least one element to display
    if (isEmpty(head))
    {
        printf("There is no element in dictionary.");
    }
    else
    {   
        //Loop until all elements are printed
        while (head != NULL)
        {
            //Display element and move to next el
            printf("%s (def): %s\n", head->word, head->definition);
            head = head->next;

            //Check if 10 elements are printed
            if (CountEl == (9 + 10 * CountPage))
            {
                //Incremenent amount of pages
                CountPage ++;

                //Display page
                printf("Page %d. Press Enter for next page.\n>>> ", CountPage);
                scanf("%d", &choice);
                printf("\n");
            }
            //Increment number of elements
            CountEl ++;
        }
    }
}

void swap(DictElement *a, DictElement *b) 
{ 
    char* tmp;
    //swap data of a and b using temp
    tmp = a->word;
    a->word = b->word; 
    b->word = tmp;
} 
*/
void SortDescending(DictElement* head)
{
    int swapped; 
    DictElement *PosPoint; 
    DictElement *NextPoint = NULL; 
  
    // Checking for empty list 
    if (head != NULL) 
    {
  
        do
        { 
            swapped = 0; 
            PosPoint = head; 
    
            while (PosPoint->next != NextPoint) 
            { 
                if (strcmp(PosPoint->word, PosPoint->next->word) <= 0)
                {  
                    swap(PosPoint, PosPoint->next); 
                    swapped = 1; 
                }

                PosPoint = PosPoint->next; 
            } 
            NextPoint = PosPoint; 
        } 
        while (swapped);
    }
}

void SortAscending(DictElement* head)
{
    int swapped; 
    DictElement *PosPoint; 
    DictElement *NextPoint = NULL; 
  
    // Checking for empty list 
    if (head != NULL) 
    {
  
        do
        { 
            swapped = 0; 
            PosPoint = head; 
    
            while (PosPoint->next != NextPoint) 
            { 
                if (strcmp(PosPoint->word, PosPoint->next->word) > 0)
                {  
                    swap(PosPoint, PosPoint->next); 
                    swapped = 1; 
                }

                PosPoint = PosPoint->next; 
            } 
            NextPoint = PosPoint; 
        } 
        while (swapped);
    }
}

void DisplayMenu(Dict *head)
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

            AddElement(index, word, definition, head);
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

            printf("The index of %s is\n>>>  %d", word, Search(head, word));
            break;

        //Sort in ascending order
        case 9:
            SortAscending(head);
            break;

        //Sort in descending order
        case 10:
            SortDescending(head);
            break;
        
        //Display dictionary by pages of 10 words
        case 11:
            DisplayDictByTen(*head);
            break;
    
        default:
            return;
    }
    printf("\n");
}




DictElement* NewElement(const char* word, const char* definition)
{
  DictElement* NewEl = (DictElement*)malloc(sizeof(DictElement));
  
  NewEl->word = copy_string(word);
  NewEl->definition = copy_string(definition);
  NewEl->next = NULL;
  
  return NewEl;
}

void RemoveDict(DictElement* Element, int recursive)
{
    if (recursive && Element->next != NULL)
    {
        /* Recursive call to delete every subsequent element */
        RemoveDict(Element->next, 1);
    }
    
    free(Element->word);
    free(Element->definition);
    free(Element);
}

Dict* NewDict(void)
{
    Dict* list = (Dict*)malloc(sizeof(Dict));
    list->size = 0;
    list->head = NULL;
    
    return list;
}

void DelDict(Dict* list)
{
    if (list->head != NULL)
    {
        RemoveDict(list->head, 1);
    }
    
    free(list);
}

int isEmpty(const Dict* list)
{
    return list->size == 0;
}

void AddElement(Dict* list, int index, const char* word, const char* definition)
{
    if (index >= 0 && index <= list->size) {
        DictElement* NewEl = NewElement(word, definition);
        
        if (index == 0) {
        NewEl->next = list->head;
        list->head = NewEl;
        }
        
        else {
        DictElement* prev = list->head;
        DictElement* next;
        
        while (--index > 0) {
            prev = prev->next;
        }
        
        next = prev->next;
        
        prev->next = NewEl;
        NewEl->next = next;
        }
        
        ++list->size;
    }
}

void NewHead(Dict* list, const char* word, const char* definition)
{
    AddElement(list, 0, word, definition);
}

void NewTail(Dict* list, const char* word, const char* definition)
{
    AddElement(list, list->size, word, definition);
}

void RemoveElement(Dict* list, int index)
{
    if (index >= 0 && index < list->size) {
        DictElement* Element;

        if (index == 0) {
        Element = list->head;
        list->head = list->head->next;
        }
        
        else {
        DictElement* prev = list->head;
        while (--index > 0) {
            prev = prev->next;
        }
        
        Element = prev->next;
        prev->next = Element->next;
        }
        
        RemoveDict(Element, 0);
        --list->size;
    }
}

void RemoveHead(Dict* list)
{
    RemoveElement(list, 0);
}

void RemoveTail(Dict* list)
{
    RemoveElement(list, list->size - 1);
}

void RemoveWord(Dict* list, const char* word)
{
    RemoveElement(list, Search(list, word));
}

int Search(const Dict* list, const char* word)
{
    DictElement* Element = list->head;
    int index = 0;
    
    while (Element != NULL) {
        if (strcmp(word, Element->word) == 0) {
        return index;
        }
        
        Element = Element->next;
        ++index;
    }
    
    return -1;
}

Dict* CopyDict(const Dict* list)
{
    Dict* new = NewDict();
    
    DictElement* Element = list->head;
    while (Element != NULL) 
    {
        NewTail(new, Element->word, Element->definition);
        Element = Element->next;
    }
    
    return new;
}

void list_sort(Dict* list)
{
    // Insertion sort algorithm 
    DictElement* node1 = list->head;
    DictElement* head = NULL;
        
    while (node1 != NULL) {
        DictElement* node2 = head;
        DictElement* prev = NULL;
        DictElement* temp = node1;
        
        while (node2 != NULL && strcmp(node1->word, node2->word) > 0)
        {
            prev = node2;
            node2 = node2->next;
        }
        
        node1 = node1->next;
        temp->next = node2;
        
        if (prev == NULL)
        {
            head = temp;
        }
        else
        {
            prev->next = temp;
        }
    }
    
    list->head = head;
}

void list_show(const Dict* list)
{
  DictElement* Element = list->head;
  int page = 0;
  
  while (Element != NULL) {
    int i;
    for (i = 0; i < 10 && Element != NULL; ++i) 
    {
        printf("%d. \"%s\": \"%s\"\n", i + page * 10, Element->word, Element->definition);
        Element = Element->next;
    }
    
    getchar(); /* input pause */
    ++page;
  }
}

//Main function
int main(int argc, char const *argv[])
{
    //Initialize array
    DictElement * head;
    head = (DictElement *) malloc(sizeof(DictElement));

    DisplayMenu(&head);

    NewHead("test", "encore un test", &head);
    NewQueue("lkager", "Wow un deuxieme test", &head);
    NewQueue("fgah", "omg trop de tests", &head);
    DisplayMenu(&head);

    FreeAll(head);

    return 0;
}