#ifndef DICTIONARY_FUNCTIONS_H
#define DICTIONARY_FUNCTIONS_H

// Element of dictionary
typedef struct DictElement
{
    //Word itself and its definition
    char* word;
    char* definition; 

    struct DictElement* next ;

} DictElement;

// Dictionary itself
typedef struct Dictionary
{
    // Size of dictionary
    int size;
    struct DictElement *head;

} Dict;

// Create dictionary
Dict* NewDict(void);

// Delete the whole dictionary
void DelDict(Dict*);

// Create a new element
DictElement* NewElement(const char*, const char*);

// Add a new element at the end of the structure
void AddElement(Dict*, const char*, const char*);

// Delete element(s) from dictionary
void RemoveDict(DictElement*, int);

// Remove word from dict
void RemoveWord(Dict*, const char*);

// Look for element in dictionary
int Search(const Dict*, const char*);

#endif