#include <stdio.h>
#include <stdlib.h>

typedef struct Item Item;

struct Item{
    float infofloat;
    char* string;
		char* key1;
    int seekstring;
    int lenstring;
    int seekkey;
    int lenkey;
    int status;//удаленный - 0
};

int makeItem(float infofloat, char* string, FILE* fd, char* key1);
void freeItem(Item* item);
void printitem(Item* item);
Item* getItem(FILE* fd, int seek);
void changestatus(FILE* fd,int seekitem);
int loaditem(FILE* fd, char** key);
