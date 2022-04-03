#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define fam 30    // max ����� �������� � �������
#define zag 50    // max ����� �������� � �������� �����
#define kol 10    // max ����� ������������ ���� � ��������

void mas_str(struct book*, struct book**);
struct book{
	char avt[fam];
	char naz[zag];
	int str, izd;
};

//void mas_str(book, book*);
//int main()  
//{
//	setlocale(LC_ALL, "Russian");
//	book bk = {}, lib[kol] = {"","",0,0};
//	int i;
//	do              // ���� �� ��� ��� ���� ��������� �������
//	{
//		fflush(stdin);
//		printf("\n������� ������� ������: ");
//		gets(bk.avt);
//		if(strcmp(bk.avt, ""))       //���� �� ������ ����
//		{
//			printf("\n������� ������������ �����: ");
//			gets(bk.naz);
//			printf("\n������� ��� ������� � ����� �������: ");
//			scanf("%d%d", &bk.izd, &bk.str);
//			mas_str(bk, lib); //���������� ��������� � ������ lib[]
//		}
//		//else break;
//	} while (strcmp(bk.avt, ""));
//	for (i = 0; lib[i].avt[0]; i++)
//		printf("\n%s    %s", lib[i].avt, lib[i].naz);
//	printf("\n");
//	return 0;
//}
//
//void mas_str(book bk, book lib[])   // ������ ���������� � ��������� ���������
//{
//	static int num;
//	int k = 0, i;
//	while(strcmp(lib[k].avt, "") && strcmp(lib[k].avt, bk.avt))
//		k++;     // ���� �� ���-��� �������� � �� ��������� � ������� ��������� ���-��
//	if(!strcmp(lib[k].avt, bk.avt))   //���� ����� ������
//	{
//		while(!strcmp(lib[k].avt, bk.avt))
//			k++;    // ����� ����� ������ �������� � ������ �������
//		i = num;    // -1 �.�. ���������� ���������� � 0
//		while(i>k)  // ����� ��������� � ������ k ...
//		{
//			lib[i] = lib[i - 1];
//			i--;
//		};
//	} 
//	lib[k++] = bk;
//	num++;
//}




// ������������ ��������� �� ���������

void mas_str(book*,book**);
int main()   
{
	setlocale(LC_ALL, "Russian");
	book *bk, **lib;
	bk = (book *)calloc(1, sizeof(book));         // {"","",0,0};
	lib = (book **)calloc(1, sizeof(book*)*kol);  // {NULL};
	do              //���� ���-�� �� ��� ��� ���� ��������� �������
	{
		fflush(stdin);
		printf("\n������� ������� ������: ");
		gets(bk->avt);
		if(strcmp(bk->avt, ""))       // ���� �� ������ ����
		{
			printf("\n������� ������������ �����: ");
			gets(bk->naz);
			printf("\n������� ��� ������� � ����� �������: ");
			scanf("%d%d", &bk->izd, &bk->str);
			mas_str(bk, lib); // ���������� ��������� � ������ lib[]
		}
	} while (strcmp(bk->avt, ""));
	for (int i = 0; lib[i]; i++)
		printf("\n%s    %s", lib[i]->avt, lib[i]->naz);
	printf("\n");
	return 0;
}

void mas_str(book *bk, book **lib)   // ������ ���������� � ��������� ���������
{
	int k = 0, i;
	static int n;
	*(lib + n) = (book *)calloc(1, sizeof(book));
	while(strcmp((*(lib + k))->avt, "") && strcmp((*(lib + k))->avt, bk->avt))
		k++;   // ���� �� ���-��� �������� � �� ��������� � ������� ��������� ���-��
	if(!strcmp((*(lib + k))->avt, bk->avt))   //���� ����� ������
	{
		while(!strcmp(((*lib + k))->avt, bk->avt))
			k++;      // ����� ����� ������ �������� � ������ �������
		i = n;        // 
		while(i > k)  // ����� ��������� � ����� ������� �� ������ k
		{
			memcpy(*(lib + i), *(lib + i - 1), sizeof(book));
			i--;
		}
	} 
	memcpy(*(lib + k), bk, sizeof(book));  // ����������� bk --> lib[k]
	n++;
}

