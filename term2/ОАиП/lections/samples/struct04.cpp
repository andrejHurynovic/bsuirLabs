#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <iostream>
// ���������� ������� ������������� ������ �� 2 �����������
//   (x1,y1)  �  (x2,y2).

struct rect analiz(struct rect); // ����� ������� ����� struct �����������
void swap(int n, struct rect *);

struct point {  // ��������� point ��������� ����������
	            // ���������� (x � y) ����� �� ���������
	int x;             
	int y;
};           
struct rect {   // ��������� rect ��������� ���������� 
	point p1;   // 2 ������� ����� (�������-��, ��������)
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
		puts("������� ���������� ������ ������� ���� ������");
		scanf("%d%d", &pt.p1.x, &pt.p1.y);
		puts("������� ���������� ������� �������� ���� ������");
		scanf("%d%d", &pt.p2.x, &pt.p2.y);
		pt = analiz(pt);       // ������ � ��������� ��������� ������� �����
	} while (pt.p1.x>pt.p2.x && pt.p1.y>pt.p2.y);
	s = (pt.p2.x - pt.p1.x)*(pt.p2.y - pt.p1.y);   // ���������� ������� ������
	printf("������� ������ S = %d", s);
	getch();
	return 0;
}

rect analiz(rect ptt)
{
	void(*f)(int, rect *) = { swap };        // ��������� �� �������   swap
	rect *ptr;
	ptr = &ptt;                            // ptr �������� ����� ���-�� ptt
	if (ptt.p1.x>ptt.p2.x) (*f)(1, ptr);  // x1>x2 ��������� � (*f)  x1<->x2
	if (ptt.p1.y>ptt.p2.y) (*f)(2, ptr);  // y1>y2 ��������� � (*f)  y1<->y2
	return ptt;
}

void swap(int n, rect *ptr)  // ������ ����������� ��������� 2 �����
{
	int i;                    // �� ������� �� ��������� �������� �.�.
	switch (n)                // ������ ����������� �� ������ ���-�� ptt
	{
	  case 1: i = ptr->p1.x; ptr->p1.x = ptr->p2.x; ptr->p2.x = i; break;
	  case 2: i = ptr->p1.y; ptr->p1.y = ptr->p2.y; ptr->p2.y = i; break;
	}
}