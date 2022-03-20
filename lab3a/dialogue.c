#include "dialogue.h"

#include <string.h>

int getInt(){
    int a;
    while(scanf("%d", &a) != 1) {
        printf("Попробуйте еще раз: ");
        while(getchar() != '\n');
    }
    getchar();
    return a;
}

float getFloat(){
    float a;
    while(scanf("%f", &a) != 1) {
        printf("Попробуйте еще раз: ");
        while(getchar() != '\n');
    }
    getchar();
    return a;
}

char* get_String(){
    char* a = (char*)malloc(1);
    char buf[11];
    int n, size = 0;
    *a = '\0';
    do{
        n = scanf("%10[^\n]", buf);
        if(n < 0){
            free(a);
            a = NULL;
            continue;
        }
        if(n == 0)
            scanf("%*c");
        else{
            size += (int)strlen(buf);
            a = (char*)realloc(a, size + 1);
            strcat(a, buf);
        }
    }while(n > 0);
    if(*(a + strlen(a) - 1) == ' '){
        for(int i = strlen(a) - 1; *(a + i) == ' '; i--)
            *(a+i) = '\0';
    }
    return a;
}

void dialogue(){
      Table* table = createtable();
      int choose;
      do {
        float infofloat;
        Item* item = NULL;
        char* info,* key;
        printf("1. Show table.\n"
        "2. Add table.\n"
        "3. Find by key.\n"
        "4. Delete from table.\n"
        "5. Special function for keyspace1.\n"
        "0. End work and delete table.\n"
        "Your choose is: ");
        choose = getInt();

          if (choose == 1){
            printf("\n");
            printkeyspace(table->keySpace1);
            printf("\n");}

          if (choose ==2){
          printf("Input info float: ");
          infofloat = getFloat();
          do{
            printf("Input info string: ");
            info = get_String();
          }while(strlen(info) < 1);

          do{
            printf("Input key string: ");
            key = get_String();
          }while(strlen(key) < 1 || strlen(key) > 4);

          item = makeItem(infofloat, info);
          if(addtable(table, item, key) == 0){
            printf("Can't find free space.\n");
            freeItem(item);
          }
          else{
            printf("Table updated.\n");
          }}

          if (choose == 3){
            printf("Input key string: ");
            key = get_String();
            int spec = special(table->keySpace1, key, key);
          
          /*if(item != NULL){
            printitem(item);
            freeItem(item);*/
            free(key);
          }
          

          if (choose == 4){                   //делит не работает если не создан кейспейс походу
            printf("Input key string: ");
            key = get_String();
          if (deletetable(table, key) == 0)
          {
            printf("unsucced delete\n");
          }
          else{
            printf("succed delete\n");
          }
            free(key);}
            if (choose == 0){
              printf("goodbye");
                fulldeletetable(table);}

                  if (choose == 5){
                    printf("Enter the first key\n");
                    char* firstkey = get_String();
                    printf("Enter the last key\n");
                    char* lastkey = get_String();
                    int spec = special(table->keySpace1, firstkey, lastkey);
                    if (spec == 1){
                      printf("succed\n");}
                    else
                      {printf("unsucced\n");}}
      } while(choose != 0);
}
