#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//#include "e:\1\1_�\function\function\A.H"  // ���������� ������� �����.
//int funk();
//int ms[3][2] = { 1, 2, 3, 4, 5, 6 };
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	system("CLS");
//	//int k=2;    // ������ ��������� �������������� ������� ����������
//	extern int k;
//	printf("\n(� main) ����� ms= %-27p ����� k= %p", ms, &k);
//	funk();        // funk(k) ������� ���������� ����� ���� ��������
//	               // � �������� ��������� � �������
//	printf("\n3: ���������  %d  ", k);
//	return 0;
//}
//
////int i;               // ��� �� ������ ���������� ������� ����������
//int funk()
//{// int i;             // �������������� (���������) ����������
//	static float j;
//	extern int k;
//	extern int ms[][2];
//	k = 1;             // ������������� k
//	k++;               // ��������� k
//	printf("\n(� funk) ����� ms= %p  �������� j= %4.2f  ����� k= %p", ms, j, &k);
//	return k++;
//}

//--------------------------------------------- 2 -----------------------------------

// ������ �������� ���������� ����� ���������
// ����������� ������������� ���������� ���������� */
//void fun(void *, int);   // ��������-��������� ����������� ����
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
	printf("\n ** �1 **   a= %d", a);
	fun4(a);
	printf("\n ** �2 **   a= %d", a);
	fun5(&a);
	printf("\n ** �3 **   a= %d", a);
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
