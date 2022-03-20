#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* skipspace(char* s){// функция которая удаляет лишние пробелы в начале строки
  int k = strcspn(s," \t");
  return s+k;
}

char* skipword(char* s){// функция которое пропускает ненужное слово
  int k = strcspn(s, " \t");
  return s + k;
}

char* copyword(char *from, char* to){// фуункция для копирования строки в переменную
  int k = strcspn(from," \t");
  strncat(to,from,k);
  to+=k;
  *to++=' ';
  *to = '\0';
  return to;
}

char* result(char* str1, char* str2){//функция вычисления результата
  char *p =(char*) malloc ((strlen(str1)+strlen(str2)) +1);//выделяем максимально возмомжную память
  char *tmp = p;//переменная, куда будем записывать слова если они подходят
  int numofw1 = 1;//счетчик чет / нечет слов для первой и второй строки
  int numofw2 = 0;
  *tmp = '\0';// изначально переменная пустая
  while (*(str1 = skipspace(str1))){// сразу же скипаем пробелы в строке, в цикле начинаем обрабатывать слова
    if (numofw1) {//если слово подходит, копируем его
      tmp = copyword(str1, tmp);
    }
    numofw1 = !numofw1;
    str1= skipword(str1);}// скипаем след слово, которое не будет подходить
    while (*(str2 = skipspace(str2))){//все то же самое для второй строки
      if (numofw2) {
        tmp = copyword(str2, tmp);
      }
      numofw2 = !numofw2;
      str2= skipword(str2);}
  if (p != tmp)//чистим от пробелов результирующую строку
    *--tmp = '\0';
  p = (char*)realloc(p,strlen(p) + 1);
  return p;
}

char* get_String(){//функция считывания строки
    char* str = (char*)malloc(1);//сделаем пока на 1 символ, потом будем увеличивать через realloc
    if(str == NULL){
        printf("memory did not allocate");
    }//проверка на выделение памяти
    char buf[11];//создаем буффер
    int n, size = 0;
    *str = '\0';//изначально пустая строка
    do{
        n = scanf("%10[^\n]", buf);//считываем 10 символов и загоняем их в буфер
        if(n < 0){//если было нажат ctrl+d
            free(str);//очищаем выделенную под память строку
            str = NULL;//делаем в стр заглушку
            return str;//заходим на след итерацию
        }
        if(n == 0){
            scanf("%*c");//если значение было считано но произошла ошибка(например несоответствие типов)
            continue;}
        else{
            size += (int)strlen(buf);//считаем длину строки
            str = (char*)realloc(str, size + 1);//перевыделяем память размера size+1 для нуль символа
            strcat(str, buf);//конкатенируем строку из буфера с изначальной строкой
        }
    }while(n > 0);
    if(*(str + strlen(str) - 1) == ' '){//удаление пробелов в конце строки
        for(int i = strlen(str) - 1; *(str + i) == ' '; i--)
            *(str+i) = '\0';
    }
    return str;
}

int main ()
{
  char* str1 = NULL;//заглушка для первой строки
  char* str2 = NULL;//для второй
  char* p = NULL;//результирующая
  //char* str2 = "!";
while(puts("enter the string"), str1 = get_String(), str2 = get_String() ){// вводим пока вводится
    //str1 = get_String();
    //printf("Enter string 2: ");
    //str2 = get_String();
    if(*str1==EOF || *str2==EOF){//если обе строки кончились выходим
        break;}
   p = result(str1, str2);//вызываем функцию вычисления результата
   printf("Result is: %s\n", p);
   free(str1);
   free(str2);
   free(p);
}
return 0;
}
