#include "item.h"

Item* makeItem(float infofloat, char* string){
  Item* item = (Item*)malloc(sizeof(Item));
  item->infofloat = infofloat;
  item->string = string;
  return item;
}
void freeItem(Item* item){
  free(item->string);
  free(item->key1);
  free(item);
}
void printitem(Item* item)
{
  printf("info: float-> %f; string-> %s.\n", item->infofloat, item->string);
}
