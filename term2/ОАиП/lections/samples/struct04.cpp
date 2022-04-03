#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <iostream>
// Нахождение площади прямоугольной фигуры по 2 коррдинатам
//   (x1,y1)  и  (x2,y2).

struct rect analiz(struct rect); // здесь наличие слова struct обязательно
void swap(int n, struct rect *);

struct point {  // структура point описывает координаты
	            // координаты (x и y) точки на плоскости
	int x;             
	int y;
};           
struct rect {   // структура rect описывает координаты 
	point p1;   // 2 угловых точек (прямоуг-ка, квадрата)
	point p2;
};  

int main()
{
	setlocale(LC_ALL, "Russian");
	rect pt;
	int s;
	do
	{
		system("cls");
		puts("введите координаты левого нижнего угла фигуры");
		scanf("%d%d", &pt.p1.x, &pt.p1.y);
		puts("введите координаты правого верхнего угла фигуры");
		scanf("%d%d", &pt.p2.x, &pt.p2.y);
		pt = analiz(pt);       // анализ и коррекция координат угловых точек
	} while (pt.p1.x>pt.p2.x && pt.p1.y>pt.p2.y);
	s = (pt.p2.x - pt.p1.x)*(pt.p2.y - pt.p1.y);   // вычисление площади фигуры
	printf("площадь фигуры S = %d", s);
	getch();
	return 0;
}

rect analiz(rect ptt)
{
	void(*f)(int, rect *) = { swap };        // указатель на функцию   swap
	rect *ptr;
	ptr = &ptt;                            // ptr содержит адрес стр-ры ptt
	if (ptt.p1.x>ptt.p2.x) (*f)(1, ptr);  // x1>x2 выполняем в (*f)  x1<->x2
	if (ptt.p1.y>ptt.p2.y) (*f)(2, ptr);  // y1>y2 выполняем в (*f)  y1<->y2
	return ptt;
}

void swap(int n, rect *ptr)  // замена одноименных координат 2 точек
{
	int i;                    // из функции не требуется возврата т.к.
	switch (n)                // замена выполняется по адресу стр-ры ptt
	{
	  case 1: i = ptr->p1.x; ptr->p1.x = ptr->p2.x; ptr->p2.x = i; break;
	  case 2: i = ptr->p1.y; ptr->p1.y = ptr->p2.y; ptr->p2.y = i; break;
	}
}