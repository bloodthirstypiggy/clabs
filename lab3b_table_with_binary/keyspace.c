#include <string.h>

#include "keyspace.h"

KeySpace1* createKeySpace1(float infofloat, char* string, char* key1, FILE* fd){
  KeySpace1* keySpace1 = (KeySpace1*)calloc(sizeof(KeySpace1), 1);
  keySpace1->key = key1;
  keySpace1->seekitem = makeItem(infofloat, string, fd, key1);
  keySpace1->next = NULL;
  return keySpace1;
}

Item* finditem(KeySpace1* keySpace1, char* key, FILE* fd){
  KeySpace1* finder = keySpace1;
  while(finder != NULL){
    if(strcmp(key, finder->key) == 0){
      return getItem(fd, finder->seekitem);
    }
    finder = finder->next;
  }
  return NULL;
}

KeySpace1* additem(KeySpace1* keySpace1,float infofloat,char* string, char* key1, int* nsize, FILE* fd){
  KeySpace1* newkeyspace = (KeySpace1*)malloc(sizeof(KeySpace1));
  
  newkeyspace->next = keySpace1;
  newkeyspace->key = key1;
  newkeyspace->seekitem = makeItem(infofloat, string, fd, key1);
  (*nsize)++;
  return newkeyspace;
}

int deleteitem(KeySpace1** keySpace1, char* key, int* nsize, FILE* fd){
  KeySpace1* deleter = *keySpace1;
  KeySpace1* helper = deleter;
  if (deleter == NULL)
  {
    return 0;
  }
  if(strcmp(key, deleter->key) == 0){
    *keySpace1 = deleter->next;
    (*nsize)--;
    changestatus(fd, deleter->seekitem);
    free(deleter->key);
    free(deleter);
    return 1;
  }

  while(strcmp(key, deleter->key) != 0)
  {
    helper = deleter;
    deleter = deleter->next;
    if(deleter == NULL)
      return 0; //0 - если не найден ключ
  }
  helper->next = deleter->next;
  changestatus(fd, deleter->seekitem);
  free(deleter->key);
  free(deleter);
  (*nsize)--;
  return 1; //1 - успешное удаление
}

void printkeyspace(KeySpace1* keySpace1, FILE* fd)
{
  KeySpace1* printer = keySpace1;
  while(printer != NULL)
  {
    Item* item = getItem(fd, printer->seekitem);
    printf("The key is -> %s.\t", printer->key);
    printitem(item);
    printer=printer->next;
    freeItem(item);
  }
}

void deletefullkeyspace1(KeySpace1* keySpace1){
  KeySpace1* deleter = keySpace1;
  KeySpace1* helper;
  while(deleter != NULL){
    helper = deleter;
    deleter = deleter->next;
    free(helper->key);
    free(helper);
  }
}
