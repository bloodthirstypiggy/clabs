#include "tree.h"

/*--------------------------------------------------------------------------------
Что делает?
1. создает новое дерево(если вызывать функцию создания дерева надо передавать
готовый айтем, который впишется в дерево, этот айтем можно создать в createitem)
2.добавляет в дерево новый элемент:
    а.если ключи равны, нужно запомнить информацию, которая лежала в дереве и
заменить ее на ту информацию, что поступила последней, а первую информацию
вывести б.если ключ меньше корня, тогда нужно проверить, тогда если слева нету
ссылки на след дерево, то добавляем в левую ссылку это дерево, если есть,
переходим к этому дереву и continue в.если больше корня -//- только идем вправо
3. Поиск элемента. Возвращает ссылку на элемент или нулл, если этот элемент не
найден ( возвращает tree->item) ФУНКЦИЯ РЕВЕРСИВНА 4.Обратный вывод. Печататет
все дерево в обратном порядке(от большего ключа к меньшему), то есть выводит
ключ, поле с цифрами и текст. ФУНКЦИЯ РЕВЕРСИВНА



не работает удаление корня! смотреть внимательно




!! не создается заново корень, подправить поиск ближайшего

-----------------------------------------------------------------------------------
*/

Tree* createTree(int key, Item* item) {
  Tree* tree = (Tree*)malloc(sizeof(Tree));

  tree->right = NULL;
  tree->left = NULL;
  tree->right = NULL;
  tree->previous = NULL;
  tree->key = key;
  tree->item = item;
  return tree;
}

void addLeft(Tree* tree, Tree* plug) {
  tree->left = plug;
  plug->previous = tree;
  plug->right = NULL;
  plug->left = NULL;
}
void addright(Tree* tree, Tree* plug) {
  tree->right = plug;
  plug->previous = tree;
  plug->right = NULL;
  plug->left = NULL;
}

int deleteroot(Tree* tree) {
  Tree* root = tree;
  if (root->left != NULL && root->right != NULL) {
    Tree* prev = findprev(root);  //ищем жертву
    copyitem(root, prev);  // копируем инфу из жертвы в рут
    root->key = prev->key;              //копируем ключ
    if (prev->previous->right == prev)  //если прев справа
    {
      if (prev->left != NULL) {
        prev->previous->right = prev->left;
        prev->left->previous = prev->previous->right;
      } else {
        prev->previous->right = NULL;
      }
    } else if (prev->previous->left == prev) {
      if (prev->left != NULL) {
        prev->previous->left = prev->left;
        prev->left->previous = prev->previous->left;
      } else {
        prev->previous->left = NULL;
      }
    }
    freeItem(prev->item);
    free(prev);
    return 1;
  } else {
    if (root->right != NULL) root->right->previous = NULL;
    if (root->left != NULL) root->left->previous = NULL;
    freeItem(root->item);
    free(root);
    return 1;
  }
}

Tree* min(Tree* tree) {
  Tree* findermin = tree;
  if (findermin == NULL) return NULL;
  if (findermin->left == NULL)
    return findermin;
  else {
    while (findermin->left != NULL) findermin = findermin->left;
    return findermin;
  }
}

Tree* max(Tree* tree) {
  Tree* findermax = tree;
  if (findermax == NULL) return NULL;
  if (findermax->right == NULL) return findermax;
  while (findermax->right != NULL) {
    findermax = findermax->right;
  }
  return findermax;
}

void freealltree(Tree* tree) {
  if (tree == NULL) {
    return;
  }
  freealltree(tree->right);
  freeItem(tree->item);
  freealltree(tree->left);
  free(tree);
}

Tree* findprev(Tree* tree) {
  Tree* helptree = max(tree->left);
  Tree* findertree = tree;
  Tree* check;
  if (helptree == NULL) {
    while (1 == 1) {
      if (findertree->previous != NULL) {
        check = findertree;
        findertree = findertree->previous;
      } else  //мы поднялись к корню, если не он предыдущий, значит предыдущего
              //нет
      {
        if (findertree->left == check || findertree->right == check) {
          return findertree;
        } else {
          return NULL;
        }
      }

      if (findertree->left == check) {
        continue;
      } else {
        return findertree;
      }
    }
  } else {
    return helptree;
  }
}

Item* addTree(Tree** first, Tree* newtree) {
  Tree* baiden = *first;
  int key = newtree->key;
  while (1 < 2) {
    if (baiden ==
        NULL) {  //если дерево было удалено, то есть нет ссылки на самый высокий
                 //корень то новое дерево которое мы добавляем должно стать им
      *first = newtree;
      return newtree->item;
    }
    if (key == baiden->key)  //если ключи совпали:
    {
      Item* equal = (baiden)->item;  //очистка equal
      baiden->item = copyitem(baiden, newtree);
      return equal;
    }
    if (key < baiden->key) {
      if (baiden->left != NULL) {
        baiden = baiden->left;
        continue;
      } else {
        addLeft(baiden, newtree);
        return baiden->item;
      }
    }
    if (key > baiden->key) {
      if (baiden->right != NULL) {
        baiden = baiden->right;
        continue;
      } else {
        addright(baiden, newtree);
        return baiden->item;
      }
    }
  }
}

Item* copyitem(Tree* tree,
               Tree* newtree)  //первое - куда копируем, второе - что копируем
{
  Item* putin = tree->item;
  putin->number = newtree->item->number;
  putin->text = (char*)malloc(strlen(newtree->item->text));
  strcpy(putin->text, newtree->item->text);
  putin->key = newtree->item->key;
  return putin;
}

/*void go(Tree* tree)
{
    if (tree != NULL)
        go(tree->right);
    printItem(tree->item);
    go(tree->left);
}*/

void printTree(Tree* tree) {
  Tree* printer = tree;
  if (printer == NULL)
  {
    return;
  }
  while (printer->right != NULL) {
    printer = printer->right;
  }
  while (printer != NULL) {
    if (printer == min(tree)) {
      printItem(printer->item);
      printer = NULL;
      continue;
    }
    printItem(printer->item);
    printer = findprev(printer);
  }
}

Tree* findkey(Tree* tree, unsigned int key) {
  Tree* finder = tree;
  while (finder != NULL)
  {
    if (finder->key > key)
      finder = finder->left;
    else if (finder->key < key)
      finder = finder->right;
    else
      return finder;
  }
  if (finder == NULL)
  {
    return NULL;
  }
}

Tree* findToDelete(Tree* first, int key){
    Tree* pointer = first;

    if (pointer == NULL)
    {
      return NULL;
    }
    while(1 == 1){
        if(pointer->key == key)
            return pointer;
        if(key < pointer->key){
            pointer = pointer->left;
        }
        else{
            pointer = pointer->right;
        }
        if(pointer == NULL)
            return NULL;
    }
}
int deleter(Tree** first, int key){
    Tree* delete = findToDelete(*first, key);
    Tree* victim;
    Tree* victim1;
    if(delete == NULL)
        return 0;
    if(delete != *first) {
        if (delete->right == NULL && delete->left == NULL) {
            if (key > delete->previous->key) {
                delete->previous->right = NULL;
                freeItem(delete->item);
                free(delete);
                return 1;
            } else {
                delete->previous->left = NULL;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        if (delete->left == NULL && delete->right != NULL) {
            Tree* pointer = delete->previous;
            if(key > pointer->key){
                pointer->right = delete->right;
                pointer->right->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
            else{
                pointer->left = delete->right;
                pointer->left->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        if(delete->left != NULL && delete->right == NULL){
            Tree* pointer = delete->previous;
            if(key > pointer->key){
                pointer->right = delete->left;
                pointer->right->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
            else{
                pointer->left = delete->left;
                delete->left->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        if(delete->left != NULL && delete->right != NULL){
           victim = findprev(delete);
          if (victim->previous->left == victim)
          {
          if (victim->left != NULL)
          {
            victim->previous->left = victim->left;
            victim->left->previous = victim->previous;
          }
          else
          {
            victim->previous->left = NULL;
          }
          delete->item->number = victim->item->number;
          strcpy(delete->item->text, victim->item->text);
          delete->item->key = victim->item->key;
          delete->key = victim->key;
          freeItem(victim->item);
          free(victim);
          return 1;
        }

        else
        {
          if (victim->left != NULL)
          {
            victim->previous->right = victim->left;
            victim->left->previous = victim->previous;
          }
          else
          {
            victim->previous->right = NULL;
          }
          delete->item->number = victim->item->number;
          strcpy(delete->item->text, victim->item->text);
          delete->item->key = victim->item->key;
          delete->key = victim->key;
          freeItem(victim->item);
          free(victim);
          return 1;
        }
      }
      }
    else{
        if(delete->left == NULL && delete->right == NULL){
            freeItem(delete->item);
            free(delete);
            *first = NULL;
            return 1;
        }
        if(delete->left == NULL && delete->right != NULL){
            *first = delete->right;
            (*first)->previous = NULL;
            freeItem(delete->item);
            free(delete);
            return 1;
        }
        if(delete->left != NULL && delete->right == NULL){
            *first = delete->left;
            (*first)->previous = NULL;
            freeItem(delete->item);
            free(delete);
            return 1;
        }
        if(delete->left != NULL && delete->right != NULL){
           victim1 = findprev(delete);
          if (victim1->previous->left == victim1)
          {
          if (victim1->left != NULL)
          {
            victim1->previous->left = victim1->left;
            victim1->left->previous = victim1->previous;
          }
          else
          {
            victim1->previous->left = NULL;
          }
          delete->item->number = victim1->item->number;
          strcpy(delete->item->text, victim1->item->text);
          delete->item->key = victim1->item->key;
          delete->key = victim1->key;
          freeItem(victim1->item);
          free(victim1);
          return 1;
        }
        else
        {
          if (victim1->left != NULL)
          {
            victim1->previous->right = victim1->left;
            victim1->left->previous = victim1->previous;
          }
          else
          {
            victim1->previous->right = NULL;
          }
          delete->item->number = victim1->item->number;
          strcpy(delete->item->text, victim1->item->text);
          delete->item->key = victim1->item->key;
          delete->key = victim1->key;
          freeItem(victim1->item);
          free(victim1);
          return 1;
        }

    }

}
}


void printTreeKeys(Tree* tree, int i) {
  if (tree == NULL) {
    return;
  }
  printTreeKeys(tree->right, i + 1);
  for (int space = 0; space < i; space++) {
    printf("  ");
  }
  printf("%d\n", tree->key);
  printTreeKeys(tree->left, i + 1);
}


Tree* closestkey(Tree* tree, unsigned int key)
{
  Tree* finder = tree;
  unsigned int finderkey = key;
  while (1 < 2) {
    if (finder ==
        NULL) {  // если дерево удалено вернем нулл
      return NULL;
    }
    if (finder->previous == NULL && finderkey == finder->key)//если корень
    {
      if (finder->left != NULL && finder->right != NULL)
      {
        Tree* maxleft = max(finder->left);
        Tree* minright = min(finder->right);
        if (abs(maxleft->key - finderkey) < abs(minright->key - finderkey))
          return maxleft;
        else
          return minright;
      }
      else if(finder->left == NULL && finder->right != NULL)
      {
        return min(finder->right);
      }
      else if (finder->right == NULL && finder->left != NULL)
      {
        return max(finder->left);
      }
      else
        return NULL;
    }
    if (finderkey < finder->key) {
      if (finder->left != NULL) {
        finder = finder->left;
      } else {
        if (finder == tree)
        {
          return tree;
        }
        if ((abs(finder->previous->key - finderkey)) < (abs(finder->key - finderkey)))//можно наабузить через маленькие числа ансайтед инт
        {
        return finder->previous;
        }
      else
      {
        return finder;
      }
    }
    }
    if (finderkey > finder->key) {
      if (finder->right != NULL) {
        finder = finder->right;

      } else {
        if (finder == tree)
          return tree;
        if ((abs(finder->previous->key - finderkey)) < (abs(finder->key - finderkey)))//можно наабузить через маленькие числа ансайтед инт
        {
        return finder->previous;
        }
      else
      {
        return finder;
      }
    }
    }
    if (finderkey == finder->key)
    {
      Tree* closeprev;
      Tree* maxleftnoroot;
      Tree* minrightnoroot;
      //найти макс из правого и запомнить
      //если есть родительская вершина, поднимаемся, если поднялись по левой ветке, продолжаем подниматься
      //если поднялись по правой, сравниваем то куда поднялись и макс из правого
      //ответ будет до чего меньше расстояние
      maxleftnoroot = max(finder->left);//если нету эти функи ретернят нулл
      minrightnoroot = min(finder->right);
      closeprev = findprev(finder);
      /*Tree* likefinder = finder;
      if (likefinder->previous->left == finder)
      {
      while (likefinder->previous != NULL)
      {
        if (likefinder->previous->left == likefinder){
          likefinder = likefinder->previous;
          if (likefinder == tree)
          {//поднялся до корня
            closeprev = tree;
            continue;
          }
          }
        else{
          closeprev = likefinder->previous;
          break;}
      }
      }
      else if (likefinder->previous->right == likefinder)
      {
      while (likefinder->previous != NULL)
      {
        if (likefinder->previous->right == likefinder){
          likefinder = likefinder->previous;
          if (likefinder == tree)
          {//поднялся до корня
            closeprev = tree;
            continue;
          }
          }
        else{
          closeprev = likefinder->previous;
          break;}
      }
      }на этой стадии мы нашли максимальный из левого и мин из правого поддеревьвев и самый близкий из предыдущих до корня. Теперь надо сравнить*/
      if (maxleftnoroot != NULL && minrightnoroot != NULL && abs(maxleftnoroot->key - finderkey)< abs(minrightnoroot->key - finderkey) && abs(maxleftnoroot->key - finderkey) < abs(closeprev->key - finderkey))
      {
          return maxleftnoroot;
      }
      else if (minrightnoroot != NULL && maxleftnoroot != NULL && abs(minrightnoroot->key - finderkey)< abs(maxleftnoroot->key - finderkey) && abs(minrightnoroot->key - finderkey) < abs(closeprev->key - finderkey))
      {
        return minrightnoroot;
      }
      else if (minrightnoroot != NULL && maxleftnoroot != NULL && abs(closeprev->key - finderkey)< abs(maxleftnoroot->key - finderkey) && abs(closeprev->key - finderkey) < abs(minrightnoroot->key - finderkey) )
      {
        return closeprev;
      }
      else if (maxleftnoroot == NULL && minrightnoroot != NULL && abs(closeprev->key - finderkey) < abs(minrightnoroot->key - finderkey))
      {
        return closeprev;
      }
      else if (maxleftnoroot == NULL && minrightnoroot != NULL && abs(closeprev->key - finderkey) > abs(minrightnoroot->key - finderkey))
      {
        return minrightnoroot;
      }
      else if (maxleftnoroot != NULL && minrightnoroot == NULL && abs(closeprev->key - finderkey) > abs(maxleftnoroot->key - finderkey))
      {
        return maxleftnoroot;
      }
      else if (maxleftnoroot != NULL && minrightnoroot == NULL && abs(closeprev->key - finderkey) > abs(maxleftnoroot->key - finderkey))
      {
        return maxleftnoroot;
      }
      else if (maxleftnoroot == NULL && minrightnoroot == NULL)
        return closeprev;
    }
  }
}

void f_timing(){
    Tree* root = NULL;
    int n = 10, key[10000], k, cnt = 1000000, i, m;
    clock_t first, last;
    while(n-- > 0){
        srand(time(NULL));
        for(i = 0; i < 10000; i++)
            key[i] = rand() * rand();
        for(i = 0; i < cnt; ){
            k = rand() * rand();
            if(addTree(&root, createTree(k, createItem(0, "0", k))) != NULL)
                i++;
        }
        m = 0;
        first = clock();
        for(i = 0; i < 10000; i++) {
            if (findkey(root, key[i]))
                m++;
        }
        last = clock();
        printf("\n%d objects found.\n", m);
        printf("test number %d. count of nodes: %d, time: %f seconds.\n", (10 - n), (10 - n) * cnt,
               (float)(last - first) / CLOCKS_PER_SEC);
    }
    freealltree(root);
}

void f_timing_delete(){
    Tree* root = NULL;
    int n = 10, key[10000], k, cnt = 1000000, i, m;
    clock_t first, last;
    while(n-- > 0){
        srand(time(NULL));
        for(i = 0; i < 10000; i++)
            key[i] = rand() * rand();
        for(i = 0; i < cnt; ){
            k = rand() * rand();
            if(addTree(&root, createTree(k, createItem(0, "0", k))))
                i++;
        }
        m = 0;
        first = clock();
        for(i = 0; i < 10000; i++) {
            if (deleter(root, key[i]))
                m++;
        }
        last = clock();
        printf("\n%d objects found.\n", m);
        printf("test number %d. count of nodes: %d, time: %f seconds.\n", (10 - n), (10 - n) * cnt,
               (float)(last - first) / CLOCKS_PER_SEC);
    }
    freealltree(root);
}
/*Tree* closestkey(Tree* tree, unsigned int key) {
  unsigned int finderkey = key;
  Tree* keytree = tree;
  Tree* maxkey = max(keytree);
  Tree* minkey = min(keytree);
  unsigned int help1;
  unsigned int help2;
  unsigned int result;
  if (maxkey->key == minkey->key) {
    if (key == maxkey->key) return NULL;
  }
  if (key > maxkey->key) {
    return maxkey;
  }
  if (key < minkey->key) {
    return minkey;
  }

  do {
    finderkey = finderkey + 1;
    help1 = help1 + 1;  //по итогу расстояние до верхнего ключа
  } while (findkey(keytree, finderkey) == NULL);
  finderkey = key;
  do {
    finderkey = finderkey - 1;
    help2 = help2 + 1;  //по итогу расстояние до нижнего ключа
  } while (findkey(keytree, finderkey) == NULL);
  if (help1 > help2)  //расстояние до верхнего ключа больше чем до нижнего
  {
    result = abs(key - help2);
    return (findkey(keytree, result));
  } else {
    result = abs(key + help1);
    return (findkey(keytree, result));
  }
} */
