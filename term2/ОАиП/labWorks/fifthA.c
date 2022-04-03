////
////  fifthA.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 4/10/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//
//#include <stdio.h>
//#include <stdlib.h>
//
//int scanNumber(char* description){
//    int number;
//    printf("%s", description);
//    do{
//        rewind(stdin);
//    } while (!scanf("%d", &number));
//    return number;
//}
//
////1. Реализовать односвязный список целочисленных значений с функцией добавления элемента в конец. Сделать возможность с клавиатуры добавить элемент, просмотреть все элементы. С клавиатуры ввести два числа: M и N. Поменять связь между элементами: разместить N-й элемент после M-го.
//
//struct Node{
//    struct Node *next;
//    int value;
//};
//
//void printList(struct Node *head){
//    struct Node *current = head;
//    while (current != NULL) {
//        printf("%d ", current->value);
//        current = current->next;
//    }
//    printf("\n");
//}
//
//struct Node* createNodeWithValue(int value){
//    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
//    node->value = value;
//    node->next = NULL;
//    return node;
//}
//
//void addAnItemToTheEndOfTheList(struct Node* head, struct Node* node){
//    while(head->next != NULL){
//        head = head->next;
//    }
//    head->next = node;
//}
//
//void elementSwitch(struct Node **head, int m, int n){
//
//    if(m == n || m == n - 1){
//        return;
//    }
//
//    struct Node *mNode;
//    struct Node *preNNode;
//    struct Node *nNode;
//
//    mNode = *head;
//    int temp = 0;
//
//    if(m != 0){
//        while(mNode->next != NULL){
//            mNode = mNode->next;
//            temp++;
//            if(temp == m){
//                break;
//            }
//        }
//    }
//
//    if(temp < m){
//        printf("Range error");
//        return;
//    }
//
//    nNode = *head;
//    preNNode = *head;
//    temp = 0;
//
//    if(n != 0){
//        while(preNNode->next != NULL){
//            if(temp >= n - 1){
//                if(preNNode->next != NULL){
//                    nNode = preNNode->next;
//                    temp++;
//                }
//                break;
//            }
//            preNNode = preNNode->next;
//            temp++;
//
//        }
//        if(temp < n){
//            printf("Range error");
//            return;
//        }
//    }
//
//    if(n == 0){
//        *head = head[0]->next;
//        preNNode->next = mNode->next;
//        mNode->next = preNNode;
//        return;
//    }
//
//    preNNode->next = nNode->next;
//    nNode->next = mNode->next;
//    mNode->next = nNode;
//    return;
//}
//
//int main(){
//    struct Node *head = createNodeWithValue(scanNumber("Enter first elemetn of the list: "));
//    int temp;
//    do{
//        do{
//            temp = scanNumber("\n0: Create and add node to the list\n1: Print list\n2: Move N after M\n");
//        }while(temp < 0 || temp > 2);
//        switch (temp) {
//            case 0:
//                addAnItemToTheEndOfTheList(head, createNodeWithValue(scanNumber("Enter new elemetn of the list: ")));
//                break;
//            case 1:
//                printList(head);
//                break;
//            case 2:{
//                int m;
//                int n;
//                do{
//                    m = scanNumber("Enter M: ");
//                }while(m < 0);
//                do{
//                    n = scanNumber("Enter N: ");
//                }while(n < 0);
//                elementSwitch(&head, m, n);
//                break;
//            }
//        }
//    }while(1);
//}
