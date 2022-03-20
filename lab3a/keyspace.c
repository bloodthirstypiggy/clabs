#include <string.h>

#include "keyspace.h"

KeySpace1* createKeySpace1(Item* item, char* key1){
  KeySpace1* keySpace1 = (KeySpace1*)calloc(sizeof(KeySpace1), 1);
  item->key1 = key1;
  keySpace1->key = key1;
  keySpace1->info = item;
  keySpace1->next = NULL;
  return keySpace1;
}

Item* finditem(KeySpace1* keySpace1, char* key){
  KeySpace1* finder = keySpace1;
  while(finder != NULL){
    if(strcmp(key, finder->key) == 0){
      return finder->info;
    }
    finder = finder->next;
  }
  return NULL;
}

KeySpace1* additem(KeySpace1* keySpace1, Item* item, char* key1, int* nsize){
  KeySpace1* newkeyspace = (KeySpace1*)malloc(sizeof(KeySpace1));
  item->key1 = key1;
  newkeyspace->next = keySpace1;
  newkeyspace->key = key1;
  newkeyspace->info = item;
  (*nsize)++;
  return newkeyspace;
}

int deleteitem(KeySpace1** keySpace1, char* key, int* nsize){
  KeySpace1* deleter = *keySpace1;
  KeySpace1* helper = deleter;
  if (deleter == NULL)
  {
    return 0;
  }
  if(strcmp(key, deleter->key) == 0){
    *keySpace1 = deleter->next;
    (*nsize)--;
    freeItem(deleter->info);
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
  freeItem(deleter->info);
  free(deleter);
  (*nsize)--;
  return 1; //1 - успешное удаление
}

void printkeyspace(KeySpace1* keySpace1)
{
  KeySpace1* printer = keySpace1;
  while(printer != NULL)
  {
    printf("The key is -> %s.\t", printer->key);
    printitem(printer->info);
    printer=printer->next;
  }
}

void deletefullkeyspace1(KeySpace1* keySpace1){
  KeySpace1* deleter = keySpace1;
  KeySpace1* helper;
  while(deleter != NULL){
    helper = deleter;
    deleter = deleter->next;
    freeItem(helper->info);
    free(helper);
  }
}
