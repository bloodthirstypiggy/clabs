#include <stdio.h>
#include <stdlib.h>

#include "item.h"

typedef struct KeySpace1 KeySpace1;

struct KeySpace1{
		char* key;			/* ключ элемента				*/
		int seekitem;		/* указатель на информацию			*/
		KeySpace1* next;		/* указатель на следующий элемент		*/
};
KeySpace1* createKeySpace1(float infofloat, char* string, char* key1, FILE* fd);
KeySpace1* additem(KeySpace1* keySpace1,float infofloat,char* string, char* key1, int* nsize, FILE* fd);
Item* finditem(KeySpace1* keySpace1, char* key, FILE* fd);
int deleteitem(KeySpace1** keySpace1, char* key, int* nsize, FILE* fd);
void printkeyspace(KeySpace1* keySpace1, FILE* fd);
void deletefullkeyspace1(KeySpace1* keySpace1);