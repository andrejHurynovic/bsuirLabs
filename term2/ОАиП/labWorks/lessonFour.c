////
////  lessonFour.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 4/7/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//
//
//struct Node{
//    int value;          //значение
//    struct Node *next; //след элемент
//};
//
////удалеиние элемента B
//
//void Print(struct Node *head){
//    struct Node *current = head;
//    while (current != NULL) {
//        printf("%d", current->value);
//        current = current->next;
//    }
//}
//
////добавление в начало списка
//void push(struct Node **head, int value){
//    if(head == NULL){
//        return;
//    }
//    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
//    node->value = value;
//    node->next = *head;
//    *head = node; //заменяем head на nodez
//}
