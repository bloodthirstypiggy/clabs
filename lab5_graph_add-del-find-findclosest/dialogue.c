#include "dialogue.h"

void dialogue(){
    Graph* graph = graphInit();
    int x, y, choose;
    char* name;
    do{
        printf("Enter 1 to print graph\n"
               "Enter 2 to add top to the graph.\n"
               "Ehter 3 to add edge of graph\n"
               "Enter 4 to delete the top.\n"
               "Enter 5 to delete the edge.\n"
               "Enter 6 to find the way from a to b.\n"
               "Enter 0 to delete graph and off.\n");
        Head* head;
        int finX, finY, m;
        HeadMassive* tree;
        choose = getInt();
        switch(choose){
            case 1:
                printGraph(graph);
                break;
            case 2:
                printf("Enter x: ");
                x = getFloat();
                printf("Enter y: ");
                y = getFloat();
                do {
                    printf("Enter the name of top: ");
                    name = get_String();
                } while(strlen(name) < 1);
                head = headInit(x, y, name);
                addHead(graph, head);
                break;
            case 3:
                printf("Enter first x: ");
                x = getFloat();
                printf("Enter first y: ");
                y = getFloat();
                printf("Enter last x: ");
                finX = getFloat();
                printf("Enter last y: ");
                finY = getFloat();
                printf("Enter the weight of edge: ");
                addWay(graph, x, y, finX, finY);
                break;
            case 4:
                printf("Enter x: ");
                x = getInt();
                printf("Enter y: ");
                y = getInt();
                deleteHead(graph, x, y);
                break;
            case 5:
                printf("Enter first x: ");
                x = getFloat();
                printf("Enter first y: ");
                y = getFloat();
                printf("Enter last x: ");
                finX = getFloat();
                printf("Enter last y: ");
                finY = getFloat();
                deleteWay(graph, x, y, finX, finY);
                break;
            case 6:
                printf("Enter first x: ");
                x = getFloat();
                printf("Enter first y: ");
                y = getFloat();
                printf("Enter last x: ");
                finX = getFloat();
                printf("Enter last y: ");
                finY = getFloat();
                tree = findFrom(graph, x, y, finX, finY);
                printf("\n");
                printWay(tree);
                printf("Конец пути!\n");
                if(tree != NULL) {
                    while (tree->prev != NULL) {
                        tree = tree->prev;
                    }
                    freeTree(tree);
                }
                break;
            default:
                break;
        }

    }while(choose != 0);
}