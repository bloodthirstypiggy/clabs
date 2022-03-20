
#include "item.h"
#include <time.h>

typedef struct Tree Tree;

struct Tree {
  Item* item;
  unsigned int key;
  Tree* left;
  Tree* right;
  Tree* previous;
};
Tree* createTree(int key, Item* item);
Item* addTree(Tree** first, Tree* plug);
void addleft(Tree* tree, Tree* plug);
void printTree(Tree* tree);
int deleter(Tree** first, int key);
void printTreeKeys(Tree* tree, int i);
Item* copyitem(Tree* baiden, Tree* newtree);
Tree* findkey(Tree* tree, unsigned int key);
void printTree(Tree* tree);
void freetree(Tree* tree);
Tree* findprev(Tree* tree);
void freealltree(Tree* tree);
void f_timing();
