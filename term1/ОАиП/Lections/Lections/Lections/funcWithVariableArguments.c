//
//  main.c
//  Var_Param
//
//  Created by Андрэй Гурыновіч on 11/14/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.


// примеры реализации функций с переменным числом параметров
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//int TestFunc(int numbers, ...){
//    int number = 0;
//    void *p = &numbers;
//    p = ((int *)p);
//        do{
//    number += *((int *)p + 1);
//            p = ((int *)p + 1);
//        } while (numbers != NULL);
//    return number;
//}


//void fun1(int k, ...){
//    int s = 0;
//    void *p;
//    p = &k;                  // p указатель на элемент стека k
//    p = ((int *)p) + 1;      // указатель на следующий элемент стека
//    while (k--){
//        s += *((int *)p);
//        p = ((int *)p) + 1;
//    }
//}
//
//int sum(int n, ...)
//{
//    int result = 0;
//    // получаем указатель на параметр n
//    for(int *ptr = &n;n>0; n--){
//        result+= *(++ptr);
//    }
//    return result;
//}
// 
//int main(void)
//{
//    printf("%d \n", sum(4, 1, 2, 3, 4));
//    printf("%d \n", sum(5, 12, 21, 13, 4, 5));
//    return 0;
//}

//int main(){
//    int a = 2, b = 3, c = 4;
//    int result = TestFunc(a, b, c, NULL);
//}

//void fun1(int, ...);    // прототип ф-ции имеющей 1 постоянный параметр
//


//void fun1(int k, ...){
//    int s = 0;
//    void *p;
//    p = &k;                  // p указатель на элемент стека k
//    p = ((int *)p) + 1;      // указатель на следующий элемент стека
//    while (k--)
//    {  s += *((int *)p);
//       p = ((int *)p) + 1;
//    }
//    printf("\n 1 сумма  элементов = %d", s);
//}
//int main(){
////    long int b1, b2;
////    long long int c1, c2, c3, c4;
//    int a1, a2, a3;
//    puts("введите 3 int :");
//    scanf("%d%d%d", &a1, &a2, &a3);
////    puts("введите 2 long int :");
////    scanf("%ld%ld", &b1, &b2);
////    puts("введите 4 long long int :");
////    scanf("%lld%lld%lld%lld", &c1, &c2, &c3, &c4);
//    fflush(stdin);
//    fun1(3, a1, a2, a3);
////    fun1(2, b1, b2);
////    fun1(4, (long int)c1, (long int)c2, (long int)c3, (long int)c4);
////    fun1(2, '1', '2');
//    return 0;
//}






//-----------------------------------------------------------------------------------
//
//#include <stdarg.h>
//
//void fun1(char *,...);    // прототип ф-ции имеющей 1 постоянный параметр
//void fun2(char *,...);
//void fun3(char *,...);
//
//int main()
//{
//  char *s1="aaa aaaa aaaa",
//       *s2="dddddd",
//       *s3="cccc cccccc  ccccc",
//       *s4= NULL;
////  fun1(s1,s2,s3,s4);
////  fun2(s1,s2,s3,NULL);
//  fun3(s1,s2,s3,s4);
//  puts("\n");
//}
//
//  // передача в функцию строк используя параметры переменной длинны
//  // считывание указателей на передаваемые в функцию строки осуществляется
//  // с использованием указателя на указатель типа  char     (char **p)
//void fun1(char *s,...)
//{ char **p;
//  p=&s;
//  puts("\n\n функция  - fun 1 -");
//  while(*p)                 // цикл пока в стеке не NULL
//  { printf("\n%s",*p);
//    p++;                    // переход к новому элементу (адресу) в стеке
//  }                         // p увеличивается на величину = разм.указателя
//}
//
//  // передача в функцию строк используя параметры переменной длинны
//  // считывание указателей на передаваемые в функцию строки осуществляется
//  // с использованием безтипового указателя на указатель    (void **p)
//void fun2(char *s,...)
//{ void **p;
//  p=(void **)&s;
//  puts("\n\n функция  - fun 2 -");
//  while(*(char **)p)    // цикл пока в стеке не NULL  (int **)p
//  { printf("\n%s",*(char **)p++);
//    //p++;                 // переход к новому элементу (адресу) в стеке
//  }                     // **p можно не приволить к типу (char **)
//}                       // приращение p равно величине указателя
//
//
//void fun3(char *s,...)
//{ va_list p;
//  va_start(p,s);                   // p устанавливается на первый переменный
//  puts("\n\n функция  - fun 3 -"); // параметр   ("bb bbb b"), первый
//  do                               // параметр ("aaa aaaa aaaa") не выводится
//  { s=va_arg(p,char *);            // переход к новому элементу (адресу) в стеке
//    printf("\n%s",s);
//  } while(s!=NULL);                // цикл пока в стеке не NULL
//}



//--------------------------------------------------------------------------------
//
//enum Type{Char,Int,Float};
//int main()
//{
//  void fun(enum Type,...);
//     fun(Char,'a','b','c','d','e','\0');
//   fun(Int,3,4,7,9,0);
//   fun(Float,1.2,(float)5,5.,(float)0);
//     return  0;
//}
//
//void fun(enum Type t,...)
//{ char c;
//  void *p=&t;
//  p=((int *)p)+1;
//  puts("\n");
//  switch(t)
//  { case Char : while(*(char *)p)
//                { printf("%c",*(char *)p);p=((int *)p)+1;} break;
//    case Int  : while(*(int *)p)
//                { printf("%3d",*(int *)p);p=((int *)p)+1;} break;
//    case Float: while(*(double *)p)
//                { printf("%5.2f",*((double *)p));p=((double *)p)+1;}
//   }
//}



//-------------------------------------------------------------------------------

// реализация функции с произвольным числом параметров различного типа
// доступ к данным (параметрам) реализован с использованием системных
// макрос ( va_list,  va_start, va_arg,  va_end).

//#include <stdarg.h>
//enum data{Int,Float} tp;
//
//void fun(int k, int l, enum data tp,...)    // k-число групп
//{
//  int si=0;
//  float sf=0;
//  va_list p;           // p - безтиповой указатель
//  va_start(p,tp);
//  while(k--)
//  { switch(tp)
//    { case Float : while(l--) // пока не считаны все переменные группы
//           sf+=va_arg(p,double);    // сумма double (float)
//           break;
//      case Int : while(l--)   // пока не считаны все переменные группы
//           si+=va_arg(p,int);       // сумма int
//    }
//    l=va_arg(p,int);          // считывается число элементов в группе (int)
//    tp=va_arg(p,enum data);   // считывается признак типа элементов группы
//  }
//  va_end(p);
//  printf("\n  si= %d   sf= %lf",si,sf);
//}
//
//int main()
//{
//  fun(3,2,Int,1,2,3,Float,1.2,.8,2.5,4,Int,2,3,4,5);
//  printf("\n");
//  return 0;
//}




//---------------------------------------------------------------------------------


//void ** fun(int,...);
//
//int main()
//{
//  float d1=1.1,d2=2.2,d3=3.3,d4=4.4;
//  int i1=5,i2=6,i3=7,i4=8;
//  void **ms;              // для возврата из fun адресов полученных сумм
//  //puts("введите целые числа");
//  //scanf("%d%d%d%d",&i1,&i2,&i3,&i4);
//  //puts("введите дробные числа");
//  //scanf("%f%f%f%f",&d1,&d2,&d3,&d4);
//  ms=fun(3,'f',3,d1,d2,d3,'i',4,i1,i2,i3,i4,'f',2,d3,d4);
//  printf(" \n  sum int= %d  sum float= %5.2f",*((int*)*ms),*((double*)*(ms+1)));
//  return 0;
//}
//       // функция суммирования чисел типа int и double
//       // результаты возвращаются в main
//void ** fun(int n,...)    // n-число групп
//{
//  int i,si=0,j;
//  void **ii;
//  double sf=0;
//  char c;
//  ii=(void **)calloc(2,sizeof(void *));
//  void *p=&n;        // p устанавливается на начало списка
//  p=((int*)p)+1;     // p передвигается на символ-тип чисел
//  while(n--)         // пока не конец всех груп
//  { c=*(char *)p;    // считывание символа-типа
//    p=((int*)p)+1;   // указатель на число переменных в группе
//    i=*(int *)p;     // считывание числа переменных в группе
//    p=((int*)p)+1;   // сдвиг указателя на первую переменную в группе
//    switch(c)
//    { case 'f' :   for(j=0;j<i;j++)
//                   {  sf+=*(double *)p;   // сумма double
//                      p=((double*)p)+1;
//                   }
//                   break;
//      case 'i' :   for(j=0;j<i;j++)
//                   { si+=*(int *)p;      // сумма int
//                     p=((int*)p)+1;
//                   }
//    }
//  }
//  ii[0]=(void*)&si; ii[1]=(void*)&sf;  // сохранение адресов полученных сумм
//  printf(" \n  si= %d  sf= %5.2lf",si,sf);
//  return ii;
//}




//---------------------------------------------------------------------------

//void fun(int,...);
//
//int main()
//{ setlocale(LC_ALL,"Russian" );
//  int *m1, *m2;
//  m1 = (int*)calloc(3,sizeof(int));
//  for (int i = 0; i < 3; i++) m1[i] = i + 1;
//  m2 = (int*)calloc(4, sizeof(int));
//  for (int i = 0; i < 4; i++) m2[i] = i + 5;
//  fun(2,3,m1,4,m2);
//  return 0;
//}
//
//void fun(int n,...)    // n-число групп
//{ int k;
//  void **ii;
//  int *jj;
//  jj = (int *)&n;
//  printf("%3d", *(int*)jj);
//  k=*(++jj);
//
//  while (1)
//  {      printf("\n");
//      printf("%3d   ", k);
//      ii = (void**)(jj+1);
//      for (int i = 0; i < k; i++)
//          printf("%3d", *(*(int**)ii + i));
//      if (!--n) break;
//      (int**)ii++; (int**)ii++;
//      jj += 2;
//      k = *jj;
//  }
//  printf("\n");
//}
