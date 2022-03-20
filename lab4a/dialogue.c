#include "dialogue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dialogue() {
  printf("Enter the first key and information in tree\n");
  printf("Key ->\n");
  int key = getInt();
  printf("float number ->");
  float number = getFloat();
  char *text;

  do {
    printf("string with variable length ->");
    text = get_String();
  } while (strlen(text) < 1);

  Tree *tree = createTree(key, createItem(number, text, key));

  int choose;
  do {
    printf(
        "\nEnter 1 to add element into the tree.\n"
        "Enter 2 to print tree with key in reverse order .\n"
        "Enter 3 to print the tree.\n"
        "Enter 4 to find element by key.\n"
        "Enter 5 to find the closest element to the given key.\n"
        "Enter 6 to delete element by key.\n"
        "Enter 7 to timing.\n"
        "Enter 0 to quit the tree.\n");
    choose = getInt();

    switch (choose) {
      case 0:
        freealltree(tree);
        printf("goodbye!");
        break;
      case 1:
        printf("Enter the key ->");
        key = getInt();
        printf("enter float number-> ");
        number = getFloat();
        do {
          printf("Enter the string->");
          text = get_String();
        } while (strlen(text) < 1);
        Item *resultitem = addTree(
            &tree,
            createTree(key, createItem(number, text, key)));  //очистка equal

        break;
      case 2:
        printf("\n\t////////////////////// Tree //////////////////////\n");
        printTree(tree);
        printf("\t////////////////////////////////////////////////////\n");
        break;
      case 3:
        printf("\n\n");
        printTreeKeys(tree, 0);
        printf("\n");
        break;
      case 4:
        printf("Enter the key to find-> ");
        key = getInt();
        Tree *foundkey = findkey(tree, key);
        if (foundkey == NULL)
          printf("No items with this key\n");
        else
          printItem(foundkey->item);
        break;
      case 5:
        printf("Enter the key to find-> ");
        key = getInt();
        Tree *closestkeya = closestkey(tree, key);
        if (closestkeya == NULL)
          printf("secret level\n");
        else
          printItem(closestkeya->item);
        break;
      case 6:
        printf("Enter key to delete-> ");
        key = getInt();
        if (deleter(&tree, key) == 1)
          printf("succed deleted\n");
        else
          printf("No element with this key\n");
        break;
        case 7:
        f_timing();
          break;
        case 8:
        f_timing_delete();
          break;
      default:
        break;
    }
  } while (choose != 0);
}
