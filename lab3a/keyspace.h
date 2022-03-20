#include <stdio.h>
#include <stdlib.h>

#include "item.h"

typedef struct KeySpace1 KeySpace1;

struct KeySpace1{
		char* key;			/* ключ элемента				*/
		Item* info;			/* указатель на информацию			*/
		KeySpace1* next;		/* указатель на следующий элемент		*/
};
KeySpace1* createKeySpace1(Item* item, char* key1);
KeySpace1* additem(KeySpace1* keySpace1, Item* item, char* key1, int* nsize);
Item* finditem(KeySpace1* keySpace1, char* key);
int deleteitem(KeySpace1** keySpace1, char* key, int* nsize);
void printkeyspace(KeySpace1* keySpace1);
void deletefullkeyspace1(KeySpace1* keySpace1);
int special(KeySpace1* keySpace1, char* firstkey, char* lastkey);
