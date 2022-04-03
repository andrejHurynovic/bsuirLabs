#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//#include "e:\1\1_с\function\function\A.H"  // объявление внешней перем.
//int funk();
//int ms[3][2] = { 1, 2, 3, 4, 5, 6 };
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	system("CLS");
//	//int k=2;    // ошибка повторное деклатировании внешней переменной
//	extern int k;
//	printf("\n(в main) адрес ms= %-27p адрес k= %p", ms, &k);
//	funk();        // funk(k) внешняя переменная может быть передана
//	               // в качестве параметра в функцию
//	printf("\n3: результат  %d  ", k);
//	return 0;
//}
//
////int i;               // так же верная декларация внешней переменной
//int funk()
//{// int i;             // автоматическая (локальная) переменная
//	static float j;
//	extern int k;
//	extern int ms[][2];
//	k = 1;             // инициализация k
//	k++;               // изменение k
//	printf("\n(в funk) адрес ms= %p  значение j= %4.2f  адрес k= %p", ms, j, &k);
//	return k++;
//}

//--------------------------------------------- 2 -----------------------------------

// пример передачи информации между функциями
// посредством использования безтиповых параметров */
//void fun(void *, int);   // параметр-указатель обобщенного типа
//int main()
//{    
//	setlocale(LC_ALL, "Russian");
//	system("CLS"); 
//	int a;
//	double d;
//	scanf("%d", &a);
//	fun(&a, 0);
//	scanf("%lf", &d);
//	fun(&d, 1);
//}
//
//void fun(void *a, int i)
//{
//	switch (i)
//	{
//	case 0: printf("\n a= %d \n", *(int*)a); break;
//	case 1: printf("\n a= %lf \n", *(double*)a); break;
//	}
//}

//--------------------------------------------- 3 -----------------------------------

int fun1(int *);
int fun2(int[]);
int fun3(int *&);

void fun4(int);
void fun5(int *);
void fun6(int &);


int main()
{    
	setlocale(LC_ALL, "Russian");
	system("CLS");
	int a = 5;
	int *ptr;
	ptr = (int*)calloc(5,sizeof(int));
	if (!ptr) return 0;
	printf("\nmain %x   %x", ptr, &ptr);
	fun1(ptr);
	printf("\nmain %x   %x", ptr, &ptr);
	fun2(ptr);
	printf("\nmain %x   %x", ptr, &ptr);
	fun3(ptr);
	printf("\n ** т1 **   a= %d", a);
	fun4(a);
	printf("\n ** т2 **   a= %d", a);
	fun5(&a);
	printf("\n ** т3 **   a= %d", a);
	fun6(a);
	puts("\n\n");
	return 0;
}

int fun1(int *ptr)
{
	printf("\nfun1 %x   %X", ptr, &ptr);
	return 0;
}
int fun2(int m[])
{
	printf("\nfun2 %x   %X", m, &m);
	return 0;
}

int fun3(int *&ptr)
{
	printf("\nfun3 %x   %X", ptr, &ptr);
	return 0;
}

void fun4(int b)
{
	printf("\n **fun4 **   b= %d", b);
	b++;
	printf("\n **fun4 **   b= %d", b);
}
void fun5(int *c)
{
	printf("\n **fun5 **   c= %d", *c);
	(*c)++;
	printf("\n **fun5 **   c= %d", *c);
}
void fun6(int &d)
{
	printf("\n **fun6 **   d= %d", d);
	d++;
	printf("\n **fun6 **   d= %d", d);
}
