#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item Item;

struct Item {
  float number;
  char* text;
  unsigned int key;
};
Item* createItem(float number, char* text, int key);
void printItem(Item* item);
void freeItem(Item* item);
