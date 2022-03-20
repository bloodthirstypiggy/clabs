#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "input.h"

#define DEFAULT_SIZE 100;

typedef struct Head Head;
typedef struct Way Way;
typedef struct Node Node;
typedef struct Graph Graph;

struct Graph{
    Head** heads;
    int size;
    int nsize;
};

struct Node{
    Way* way;
    Node* next;
};

struct Way{
    float m;
    Head* to;
};

struct Head{
    Node* ways;
    float x;
    float y;
    char* name;
    char color;
};

typedef struct HeadMassive HeadMassive;
typedef struct DynArray DynArray;

struct HeadMassive{
    float h;
    Head* head;
    HeadMassive** heads;
    HeadMassive* prev;
    int massSize;
};

struct DynArray{
    HeadMassive** heads;
    int size;
    int nsize;
};

float resultWay(Head* first, Head* last);
Head* headInit(float x, float y, char* name);
Graph* graphInit();
int addHead(Graph* graph, Head* head);
int addWay(Graph* graph, float startX, float startY, float finX, float finY);
int deleteHead(Graph* graph, float x, float y);
int deleteWay(Graph* graph, float startX, float startY, float finX, float finY);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);
HeadMassive* findFrom(Graph* graph, float startX, float startY, float finX, float finY);
Way** findWay(Graph* graph, float startX, float startY, float finX, float finY);
Graph** graphs(Graph* graph);

#endif //LAB5_GRAPH_H