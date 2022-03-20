#include "keyspace.h"

typedef struct Table Table;

struct Table{
  KeySpace1* keySpace1;
  int nsize;
};

Table* createtable();
Item* findtable(Table* table, char* key);
int addtable(Table* table, Item* item, char* key);
int deletetable(Table* table, char* key);
void fulldeletetable(Table* table);
