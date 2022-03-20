#include "item.h"
Item* createItem(float number, char* text, int key) {
  Item* item = (Item*)malloc(sizeof(Item));
  item->number = number;
  item->text = text;
  item->key = key;
  return item;
}

void printItem(Item* item) {
  printf("Key: %d. Information: %f, %s.\n", item->key, item->number,
         item->text);
}

void freeItem(Item* item) {
  free(item->text);
  free(item);
}
