#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define fam 30    // max число символов в фамилии
#define zag 50    // max число символов в названии книги
#define kol 10    // max число наименований книг в каталоге

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
//	do              // цикл до тех пор пока выражение истинно
//	{
//		fflush(stdin);
//		printf("\n¬ведите фамилию автора: ");
//		gets(bk.avt);
//		if(strcmp(bk.avt, ""))       //если не пустой ввод
//		{
//			printf("\n¬ведите наименование книги: ");
//			gets(bk.naz);
//			printf("\n¬ведите год издани€ и число страниц: ");
//			scanf("%d%d", &bk.izd, &bk.str);
//			mas_str(bk, lib); //сохранение структуры в массив lib[]
//		}
//		//else break;
//	} while (strcmp(bk.avt, ""));
//	for (i = 0; lib[i].avt[0]; i++)
//		printf("\n%s    %s", lib[i].avt, lib[i].naz);
//	printf("\n");
//	return 0;
//}
//
//void mas_str(book bk, book lib[])   // вводит информацию в очередную структуру
//{
//	static int num;
//	int k = 0, i;
//	while(strcmp(lib[k].avt, "") && strcmp(lib[k].avt, bk.avt))
//		k++;     // цикл по стр-рам непустым и не совпающим с автором введенной стр-ры
//	if(!strcmp(lib[k].avt, bk.avt))   //если автор найден
//	{
//		while(!strcmp(lib[k].avt, bk.avt))
//			k++;    // поиск далее номера стуктуры с другим автором
//		i = num;    // -1 т.к. индексаци€ начинаетс€ с 0
//		while(i>k)  // сдвиг элементов с номера k ...
//		{
//			lib[i] = lib[i - 1];
//			i--;
//		};
//	} 
//	lib[k++] = bk;
//	num++;
//}




// демонстраци€ указател€ на структуру

void mas_str(book*,book**);
int main()   
{
	setlocale(LC_ALL, "Russian");
	book *bk, **lib;
	bk = (book *)calloc(1, sizeof(book));         // {"","",0,0};
	lib = (book **)calloc(1, sizeof(book*)*kol);  // {NULL};
	do              //цикл вып-с€ до тех пор пока выражение истинно
	{
		fflush(stdin);
		printf("\n¬ведите фамилию автора: ");
		gets(bk->avt);
		if(strcmp(bk->avt, ""))       // если не пустой ввод
		{
			printf("\n¬ведите наименование книги: ");
			gets(bk->naz);
			printf("\n¬ведите год издани€ и число страниц: ");
			scanf("%d%d", &bk->izd, &bk->str);
			mas_str(bk, lib); // сохранение структуры в массив lib[]
		}
	} while (strcmp(bk->avt, ""));
	for (int i = 0; lib[i]; i++)
		printf("\n%s    %s", lib[i]->avt, lib[i]->naz);
	printf("\n");
	return 0;
}

void mas_str(book *bk, book **lib)   // вводит информацию в очередную структуру
{
	int k = 0, i;
	static int n;
	*(lib + n) = (book *)calloc(1, sizeof(book));
	while(strcmp((*(lib + k))->avt, "") && strcmp((*(lib + k))->avt, bk->avt))
		k++;   // цикл по стр-рам непустым и не совпающим с автором введенной стр-ры
	if(!strcmp((*(lib + k))->avt, bk->avt))   //если автор найден
	{
		while(!strcmp(((*lib + k))->avt, bk->avt))
			k++;      // поиск далее номера стуктуры с другим автором
		i = n;        // 
		while(i > k)  // сдвиг элементов с конца массива до номера k
		{
			memcpy(*(lib + i), *(lib + i - 1), sizeof(book));
			i--;
		}
	} 
	memcpy(*(lib + k), bk, sizeof(book));  // копирование bk --> lib[k]
	n++;
}

