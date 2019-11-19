#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictHeader.h"

// Allocate memory and copy string
char* MemAndcopyString(const char* string)
{
    // Dynamically allocate memory
    char *newPlace = (char*)malloc(sizeof(char) * (strlen(string) +1));
    // Move string into its allocated memory storage
    strcpy(newPlace, string);

    return newPlace;
}

// Create a new element
DictElement* NewElement(const char* word, const char* definition)
{
    DictElement* NewEl = (DictElement*)malloc(sizeof(DictElement));
    
    NewEl->word = MemAndcopyString(word);
    NewEl->definition = MemAndcopyString(definition);
    NewEl->next = NULL;
    
    return NewEl;
}

// Delete element(s) from dictionary
void RemoveDict(DictElement* Element, int recursive)
{
    // Check if last element and recursive
    if (recursive && Element->next != NULL)
    {
        /* Recursive call to delete every subsequent element */
        RemoveDict(Element->next, 1);
    }
    
    // Remove element
    free(Element->word);
    free(Element->definition);
    free(Element);
}

// Create dictionary
Dict* NewDict(void)
{
    Dict* list = (Dict*)malloc(sizeof(Dict));
    list->size = 0;
    list->head = NULL;
    
    return list;
}

// Delete the whole dictionary
void DelDict(Dict* list)
{
    if (list->head != NULL)
    {
        RemoveDict(list->head, 1);
    }
    
    free(list);
}

// Add a new element at the end of the structure
void AddElement(Dict* list, const char* word, const char* definition)
{
    // Create element
    DictElement* NewEl = NewElement(word, definition);

    // Get size of actual dict
    int dictSize = list -> size;

    // Check if dict is empty
    if (dictSize == 0)
    {
        // Update pointers to make element the first
        NewEl->next = list->head;
        list->head = NewEl;
    }
    // Dict not empty
    else
    {
        DictElement* prev = list->head;
        DictElement* following;
        // Loop until we reach the end
        while (dictSize-- > 0)
        {
            prev = prev->next;
        }
        // Move pointer to next element
        following = prev->next;
        prev->next = NewEl;
        NewEl->next = following;
    }
    // Increase size of dict
    list ->size ++;
}

// Remove word from dict
void RemoveWord(Dict* list, const char* word)
{
    // Get index of word to delete
    int index = Search(list, word);

    if (index == -1)
    {
        printf("Word not found.");
    }
    
    // Check that index is in the list
    else if (index >= 0 && index < list->size)
    {
        DictElement* Element;

        // If element is the first
        if (index == 0)
        {
            Element = list->head;
            list->head = list->head->next;
        }
        
        // element not the first
        else
        {
            DictElement* prev = list->head;
            // Loop until all element's pointers are moved
            while (index-- > 0)
            {
                prev = prev->next;
            }   

            Element = prev->next;
            prev->next = Element->next;
        }
        
        RemoveDict(Element, 0);
        list->size--;
    }
}

// Look for element in dictionary
int Search(const Dict* list, const char* word)
{
    // Get first element
    DictElement* Element = list->head;

    // Initialize counter index
    int index = 0;
    
    // Loop on all elements
    while (Element != NULL)
    {
        // Check if it's the element we're looking for
        if (strcmp(word, Element->word) == 0)
        {
            // Return index if we found the word
            return index;
        }
        
        // Move pointer to next element
        Element = Element->next;

        // Increase index counter
        index++;
    }
    
    return -1;
}

DictElement* getWord(const Dict* list, const char* word)
{
    DictElement* element = (DictElement*)malloc(sizeof(DictElement));
    // Check if word is in dict
    int isIn = Search(list, word);
    if (isIn == -1)
    {
        printf("Word not in dictionary");
    }

    // Element is in dict
    else
    {
        element = list->head;

        // Loop on all elements
        while (element != NULL)
        {
            // Check if it's the element we're looking for
            if (strcmp(word, element->word) == 0)
            {
                // Terminate function by returning this element
                return element;
            }
            // Move pointer to next element
            element = element->next;
        }
    }
    // Element not in dict
    return NULL;
}

