#include "keyspace.h"

typedef struct Table Table;

struct Table{
  KeySpace1* keySpace1;
  int nsize;
};

int special(KeySpace1* keySpace1, char* firstkey, char* lastkey, FILE* fd);
Table* createtable();
Item* findtable(Table* table, char* key, FILE* fd);
int addtable(Table* table, float infofloat, char* string, char* key,FILE* fd);
int deletetable(Table* table, char* key, FILE* fd);
void fulldeletetable(Table* table);
int loadTable(FILE* fd, Table* table);