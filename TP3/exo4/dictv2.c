#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Word {
  char* key;
  char* value;
  struct Word* prev;
  struct Word* next;
} Word;

typedef struct Dict {
  int size;
  struct Word* first;
  struct Word* last;
}Dict;


char* copy_string(const char* string)
{
  char* new = (char*)malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(new, string);
  
  return new;
}

Word* newWord(const char* key, const char* value)
{
  Word* word = (Word*)malloc(sizeof(Word));
  
  word->key = copy_string(key);
  word->value = copy_string(value);
  word->prev = NULL;
  word->next = NULL;
  
  return word;
}

void deleteWord(Word* word, int recursive)
{
  if (recursive && word->next != NULL) {
    // Recursive mode to remove all words
    deleteWord(word->next, 1);
  }
  
  free(word->key);
  free(word->value);
  free(word);
}

Dict* newDict(void)
{
  Dict* dict = (Dict*)malloc(sizeof(Dict));
  dict->size = 0;
  dict->first = NULL;
  dict->last = NULL;
  
  return dict;
}

void deleteDict(Dict* dict)
{
  if (dict->first != NULL) {
    deleteWord(dict->first, 1);
  }
  
  free(dict);
}

bool isEmpty(const Dict* dict)
{
    if (dict->size == 0){
        return true;
    }
    return false;
}

void addWord(Dict* dict, int index, const char* key, const char* value)
{
  if (index >= 0 && index <= dict->size) {
    Word* word = newWord(key, value);
    
    if (index == 0) {
      word->next = dict->first;
      dict->first = word;
    }
    
    else {
      Word* prev = dict->first;
      Word* next;
      
      while (--index > 0) {
        prev = prev->next;
      }
      
      next = prev->next;
      
      if (next != NULL) {
        next->prev = word;
      }
      
      prev->next = word;
      word->next = next;
      word->prev = prev;
    }
    
    if (index == dict->size++) {
      dict->last = word;
    }
  }
}

void dictNewHead(Dict* dict, const char* key, const char* value)
{
  addWord(dict, 0, key, value);
}

void dictNewTail(Dict* dict, const char* key, const char* value)
{
  addWord(dict, dict->size, key, value);
}


int dictSearch(const Dict* dict, const char* key)
{
  Word* word = dict->first;
  int index = 0;
  
  while (word != NULL) {
    if (strcmp(key, word->key) == 0) {
      return index;
    }
    
    word = word->next;
    ++index;
  }
  
  return -1;
}

void dictRemove(Dict* dict, int index)
{
  if (index >= 0 && index < dict->size) {
    Word* word;

    if (index == 0) {
      word = dict->first;
      dict->first = dict->first->next;
      
      if (dict->first != NULL) {
        dict->first->prev = NULL;
      }
    }
    
    else {
      Word* prev = dict->first;
      Word* next;
      while (--index > 0) {
        prev = prev->next;
      }
      
      word = prev->next;
      next = word->next;
      prev->next = next;
      
      if (next != NULL) {
        next->prev = prev;
      }
    }
    
    if (index == --dict->size) {
      dict->last = word->prev;
    }
   
    deleteWord(word, 0);
  }
}

void dictRemoveHead(Dict* dict)
{
  dictRemove(dict, 0);
}

void dictRemoveTail(Dict* dict)
{
  dictRemove(dict, dict->size - 1);
}

void dictRemoveKey(Dict* dict, const char* word)
{
  dictRemove(dict, dictSearch(dict, word));
}



Dict* dictCopy(const Dict* dict)
{
  Dict* new = newDict();
  
  Word* word = dict->first;
  while (word != NULL) {
    dictNewTail(new, word->key, word->value);
    word = word->next;
  }
  
  return new;
}

void dictSort(Dict* dict)
{
  /* Insertion sort algorithm */
  Word* node1 = dict->first;
  Word* head = NULL;
  Word* tail = NULL;
      
  while (node1 != NULL) {
    Word* node2 = head;
    Word* prev = NULL;
    Word* temp = node1;
    
    while (node2 != NULL && strcmp(node1->key, node2->key) > 0) {
      prev = node2;
      node2 = node2->next;
    }
    
    node1 = node1->next;
    temp->next = node2;
    temp->prev = prev;
    
    if (prev == NULL) {
      head = temp;
    }
    else {
      prev->next = temp;
    }
    
    if (temp->next == NULL) {
      tail = temp;
    }
    else {
      temp->next->prev = temp;
    }
  }
  
  dict->first = head;
  dict->last = tail;
}

void dictDisplay(const Dict* dict)
{
  Word* word = dict->first;
  int page = 0;
  
  while (word != NULL) {
    int i;
    for (i = 0; i < 10 && word != NULL; ++i) {
      printf("%d. \"%s\": \"%s\"\n", i + page * 10, word->key, word->value);
      word = word->next;
    }
    
    getchar(); /* input pause */
    ++page;
  }
}

void dictMenu(Dict* dict)
{
  int choice;
  int index;
  char key[1024];
  char value[1024];

  for (;;) { /* endless loop */
    printf(" 0. Exit\n"
           " 1. Insert item at index\n"
           " 2. Insert head\n"
           " 3. Insert tail\n"
           " 4. Remove item at index\n"
           " 5. Remove head\n"
           " 6. Remove tail\n"
           " 7. Remove item by key\n"
           " 8. Search index by key\n"
           " 9. Sort dict\n"
           "10. Show dict\n"
           "> ");
    
    scanf("%d", &choice);
  
    switch (choice) {
      case 1:
        printf("Index: ");  scanf("%d", &index);
        printf("Key: ");    scanf("%s", key);
        printf("Value: ");  scanf("%s", value);
        addWord(dict, index, key, value);
        break;
        
      case 2:
        printf("Key: ");    scanf("%s", key);
        printf("Value: ");  scanf("%s", value);
        dictNewHead(dict, key, value);
        break;
        
      case 3:
        printf("Key: ");    scanf("%s", key);
        printf("Value: ");  scanf("%s", value);
        dictNewTail(dict, key, value);
        break;
      
      case 4:
        printf("Index: ");  scanf("%d", &index);
        dictRemove(dict, index);
        break;
      
      case 5:
        dictRemoveHead(dict);
        break;
      
      case 6:
        dictRemoveTail(dict);
        break;
      
      case 7:
        printf("Key: ");    scanf("%s", key);
        dictRemoveKey(dict, key);
        break;
      
      case 8:
        printf("Key: ");    scanf("%s", key);
        printf("The index of \"%s\" is %d\n", key, dictSearch(dict, key));
        break;
      
      case 9:
        dictSort(dict);
        break;
       
      case 10:
        dictDisplay(dict);
        break;
      
      default:
        return;
    }
    
    printf("\n");
  }
}


int main(int argc, char const *argv[])
{
    Dict* dict = newDict();
    dictNewTail(dict, "bonjour", "hello");
    dictNewTail(dict, "salut", "hi");
    addWord(dict, 1, "aurevoir", "goodbye");
    dictNewHead(dict, "souris", "mouse");
    dictDisplay(dict);
    Dict* copy = dictCopy(dict);
    deleteDict(dict);
    dictDisplay(copy);
    dictMenu(copy);

    return 0;
}
