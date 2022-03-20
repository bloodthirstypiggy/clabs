#include <string.h>

#include "table.h"

Table* createtable(){
  Table* table = (Table*)calloc(sizeof(Table), 1);
  table->nsize = 0;
  return table;
}

Item* findtable(Table* table, char* key, FILE* fd){
  Item* item = finditem(table->keySpace1, key,fd);
  if (item == NULL){
    return NULL;//если не нашли элемент
  }
  return item;
}

int addtable(Table* table, float infofloat, char* string, char* key,FILE* fd){
  if (table->nsize == 0)
  {
    table->keySpace1 = createKeySpace1(infofloat, string, key, fd);
    (table->nsize)++;
    return 1; //Успешная добавляшка итема
  }
  Item* item = finditem(table->keySpace1, key, fd);
  if(item == NULL){
    table->keySpace1 = additem(table->keySpace1,infofloat,string,key,&table->nsize,fd);
    return 1;
  }
  else{
    freeItem(item);
    return 0;
  }
}

int deletetable(Table* table, char* key, FILE* fd){
  return deleteitem(&(table->keySpace1), key, &(table->nsize), fd);
}

void fulldeletetable(Table* table)
{
  if(table->keySpace1 == NULL){
    free(table);
    return;
  }
  deletefullkeyspace1(table->keySpace1);
  free(table);
}

KeySpace1* findflitem(KeySpace1* keySpace1, char* key1)
{
  KeySpace1* finder = keySpace1;

  while (*(finder->key) != *(key1))
  {
    if (finder->next != NULL)
      finder = finder->next;
    else
      return NULL;
  }
  return finder;
}


 int special(KeySpace1* keySpace1, char* firstkey, char* lastkey, FILE* fd)
{
  KeySpace1* finder = keySpace1;
  if (keySpace1 == NULL)
    return 0;



  //теперь вроде все правильно, можно начинать создание и копирование
  Table* specialtable = createtable();
  while (finder != NULL)
  {
    if (strcmp(firstkey, finder->key)<=0 && strcmp(lastkey, finder->key)>=0)
    {
    if (specialtable->nsize == 0)
    {
      KeySpace1* keySpace1 = malloc(sizeof(KeySpace1));
      keySpace1->key = malloc(strlen(finder->key)+1);
      specialtable->keySpace1 = keySpace1;
      strcpy(specialtable->keySpace1->key,finder->key);
      keySpace1->seekitem = finder->seekitem;
      keySpace1->next = NULL;
      (specialtable->nsize)++;
    }
    else
    {
      KeySpace1* keySpace1 = malloc(sizeof(KeySpace1));
      keySpace1->key = malloc(strlen(finder->key)+1);
      strcpy(specialtable->keySpace1->key,finder->key);
      keySpace1->seekitem = finder->seekitem;
      keySpace1->next = specialtable->keySpace1;
      specialtable->keySpace1 = keySpace1;
      (specialtable->nsize)++;
    }
  }
  finder = finder->next;
  }
  printkeyspace(specialtable->keySpace1, fd);
  fulldeletetable(specialtable);
  return 1;
}


int loadTable(FILE* fd, Table* table)
{
  for(int i = 0; i < table->nsize;){
  KeySpace1* ks1 =malloc(sizeof(KeySpace1));
  ks1->seekitem = loaditem(fd, &ks1->key);
  if(ks1->seekitem == -1){
      free(ks1);
      continue;
  }
  ks1->next = NULL;
  if (table->nsize == 0)
  {
    table->keySpace1 = ks1;
    i++;
  }
  else{
    ks1->next = table->keySpace1;
    table->keySpace1 = ks1;
    i++;
  }
  }
  return 0;
}