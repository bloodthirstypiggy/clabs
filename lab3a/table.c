#include <string.h>

#include "table.h"

Table* createtable(){
  Table* table = (Table*)calloc(sizeof(Table), 1);
  table->nsize = 0;
  return table;
}

Item* findtable(Table* table, char* key){
  Item* item = finditem(table->keySpace1, key);
  if (item == NULL){
    return NULL;//если не нашли элемент
  }
  Item* newitem = (Item*)malloc(sizeof(Item*));
  newitem->infofloat = item->infofloat;
  newitem->key1 = (char*)malloc(sizeof(char) * strlen(item->key1));
  strcpy(newitem->key1, item->key1);
  newitem->string = (char*)malloc(sizeof(char) * strlen(item->string));
  strcpy(newitem->string, item->string);
  return newitem;
}

int addtable(Table* table, Item* item, char* key){
  if (table->nsize == 0)
  {
    table->keySpace1 = createKeySpace1(item, key);
    (table->nsize)++;
    return 1; //Успешная добавляшка итема
  }
  if(finditem(table->keySpace1, key) == NULL){
    table->keySpace1 = additem(table->keySpace1, item, key, &(table->nsize));
    return 1;
  }
  else{
    return 0;
  }
}

int deletetable(Table* table, char* key){
  return deleteitem(&(table->keySpace1), key, &(table->nsize));
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


int special(KeySpace1* keySpace1, char* firstkey, char* lastkey)
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
    char* string = (char*)malloc(strlen(finder->info->string)+1);
    char* key = (char*)malloc(strlen(finder->key)+1);
    strcpy(string, finder->info->string);
    strcpy(key, finder->key);
    Item* specialitem = makeItem(finder->info->infofloat,string);
    if(addtable(specialtable, specialitem, key) == 0)
    {
      printf("Something went wrong\n");
      freeItem(specialitem);
      free(key);
      return 0;//почему-то не добавился в стол элемент или не создался кейспейс
    }
  }
  finder = finder->next;
  }
  printkeyspace(specialtable->keySpace1);
  fulldeletetable(specialtable);
  return 1;
}
