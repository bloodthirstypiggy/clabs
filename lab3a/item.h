#include <stdio.h>
#include <stdlib.h>

typedef struct Item Item;

struct Item{
    float infofloat;
    char* string;
		char* key1;
};

Item* makeItem(float infofloat, char* string);
void freeItem(Item* item);
void printitem(Item* item);