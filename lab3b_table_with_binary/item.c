#include <string.h>

#include "item.h"


void freeItem(Item* item){
  free(item->string);
  free(item->key1);
  free(item);
}

int loaditem(FILE* fd, char** key)
{
  int seek = ftell(fd);
  Item* item = getItem(fd, seek);
  if (item->status == 0)
  {
    freeItem(item);
    return -1;
  }
  
  *key = item->key1;
  free(item->string);
  free(item);
  return seek;
}

int makeItem(float infofloat, char* string, FILE* fd, char* key1){
  Item* item = (Item*)malloc(sizeof(Item));
  item->status = 1;
  item->infofloat = infofloat;
  item->string = string;
  fseek(fd, 0, SEEK_END);
  int seekitem = ftell(fd);
  fwrite(item, sizeof(Item), 1, fd);
  item->seekstring = ftell(fd);
  item->lenstring = strlen(string)+ 1;
  fwrite(string, item->lenstring, 1, fd);
  item->seekkey = ftell(fd);
  item->lenkey = strlen(key1)+ 1;
  fwrite(key1, item->lenkey, 1, fd);
  fseek(fd, seekitem, SEEK_SET);
  fwrite(item, sizeof(Item), 1 ,fd);

  free(string);
  free(item);
  return seekitem;
}

void printitem(Item* item)
{
  printf("info: float-> %f; string-> %s.\n", item->infofloat, item->string);
}

Item* getItem(FILE* fd, int seek)
{
  fseek(fd, seek, SEEK_SET);
  Item* item = malloc(sizeof(Item));
  fread(item, sizeof(Item), 1, fd);
  item->string = malloc(item->lenstring);
  fread(item->string, item->lenstring, 1, fd);
  item->key1 = malloc(item->lenkey);
  fread(item->key1, item->lenkey, 1, fd);
  return item;
}

void changestatus(FILE* fd,int seekitem)
{
  Item* item = getItem(fd, seekitem);
  item->status = 0;
  fseek(fd, seekitem, SEEK_SET);
  fwrite(item, sizeof(Item), 1, fd);
  freeItem(item);
}
