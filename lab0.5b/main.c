#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
  char c;
  struct Item* next;
} item;

item* addelem(item *lst)
{
  item *temp, *p;
  temp = (item*)malloc(sizeof(item*));
  p = lst->next; // сохранение указателя на следующий узел
  lst->next = temp; // предыдущий узел указывает на создаваемый
  temp->c = ' '; // сохранение поля данных добавляемого узла
  temp->next = p; // созданный узел указывает на следующий элемент
  return(temp);
}

int isEmptyBuffer(char* buf, int count)
{
    for(int i=0;i<count;++i){
        if(buf[i])
           return 1;
    }
    return 0;
}

item* next(item* string) {
  item* current = string;
  if (current->next != NULL) {
    current = current->next;
    string = current;
  }
  return string;
}

item* findl(item* p) {
  item* temp = p;
  item* next;
  while (temp->next != NULL) {
    next = temp->next;
    temp = next;
  }
  return temp;
}

void print(item* first) {
  item* current = first;
  while (first->next != NULL) {
    printf("%c", current->c);
    current = first->next;
    first = current;
  }
  printf("%c", current->c);
}

void deleteList(item* head) {
  item* current = head;
  item* next;
  while (current->next != NULL) {
    current->c = '\0';
    next = current->next;
    free(current);
    current = next;
  }
}

item* deleteone(item* string) {
  item* current = string;
  item* next;
  current->c = '\0';
  next = current->next;
  free(current);
  current = next;
  return current;
}

int getList(item** pptr) {
  char buf[81];
  char* str;
  int i=0;
  int numofwhile = 0;
  item head = {'*', NULL};
  item* last = &head;
  int n, rc = 1;
  do {
    n = scanf("%80[^\n]", buf);
    if (n < 0) {
      deleteList(&head);
      rc = 0;
      continue;
    }
    if (n > 0) {
      for(str=buf; *str!='\0'; ++str){
      if (buf[i] !=' ') {
      last->next=(item*) malloc(sizeof(item));
      last= last->next;
      last->c = *str;
    }
    ++i;
  }
      last->next = NULL;
    }
    else if ((isEmptyBuffer(buf, 81) == 1) && (numofwhile == 0)){
      printf("You entered the empty string. Power down...\n");
      rc = 0;
      return rc;
    }
    else if(last == &head){
      rc=0;
      return rc;
    }
    else {
      scanf("%*c");
    }
    ++numofwhile;
  } while (n > 0);
  *pptr = head.next;
  return rc;
}

item* reorg(item* string) {
  char fel = string->c;
  item* lel1 = findl(string);
  char lel=lel1->c;
  item* head = string;
  printf("first element is: %c\n", fel);
  printf("last element is: %c\n", lel);
  while (string->next != NULL) {
    if (string->c == fel) {
      string->c = '\0';
      string = next(string);
      while (string->c != lel) {
        string = next(string);
        continue;
      }
      //мы должны здесь добавить новый пустой элемент затем перейти к след. если он не последний
      //мы дошли до последнего, его нужно удалить, и потом удалять все элементы
      //до первого.
      while (string->c != fel) {
        if (string->next != NULL) {
          string->c = '\0';
          item* find=string->next;
          if (find->c == fel){
            string = addelem(string);
            string=next(string);
          }
          else{
          string = next(string);}
          //item* find=string->next;
          //if (find->c == fel){
            //string = addelem(string);
            //string=next(string);
          //}
        } else {
          string->c = '\0';
          return head;
        }
      }
    }
  }
  return head;
}

int main() {
  item* string;
  while (puts("Enter the string"), getList(&string)) {
    print(string);
    printf("\n");
    string = reorg(string);
    print(string);
    printf("\n");
    deleteList(string);
  }
  return 0;
}
