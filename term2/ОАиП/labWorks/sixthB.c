////
////  sixthB.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 4/21/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//
////2. Реализовать кольцо, содержащее структуру “ПК”, функции добавления и вывода элементов. Структура “ПК” содержит идентификатор, флаг, отображающий, включен ли ПК. Добавить возможность отправить информацию от ПК с идентификатором I к ПК с идентификатором J. Идентификаторы задать с клавиатуры. При получении информации ПК с идентификатором J вывести все ПК, через которые прошла информация пока не достигла цель. Добавить возможность выключить любой ПК, при этом через выключенный ПК информация дальше не проходит.
//
//
//typedef struct PC{
//    char ID[256];
//    int power;
//}PC;
//
//typedef struct Node{
//    PC pc;
//    struct Node *left;
//    struct Node *right;
//}Node;
//
//PC createPC(){
//    PC pc;
//    printf("Enter PC ID (max 255): ");
//    rewind(stdin);
//    fgets(pc.ID, 256, stdin);
//    
//    int isEnabled;
//    do{
//        rewind(stdin);
//        printf("Is this PC turned turned on (0/1): ");
//        
//    }while(!scanf("%d", &isEnabled) || (isEnabled != 0 && isEnabled != 1));
//    pc.power = isEnabled;
//    
//    return pc;
//}
//
//
//
//void add(Node **head, PC pc) {
//    Node *tempNode = (Node*)malloc(sizeof(Node));
//    tempNode->pc = pc;
//    tempNode->left = NULL;
//    tempNode->right = NULL;
//    if (*head == NULL) {
//        *head = tempNode;
//        tempNode->left = tempNode;
//        tempNode->right = tempNode;
//        return;
//    }
//    Node *currentTail = (*head)->right;
//    (*head)->right = tempNode;
//    currentTail->left = tempNode;
//    tempNode->left = *head;
//    tempNode->right = currentTail;
//}
//
//int printAllThePCS(Node *head) {
//    Node *node = head;
//    int i = -1;
//    do{
//        i++;
//        printf("PC [%d] with ID: %s       power:   %d\n", i, node->pc.ID, node->pc.power);
//        node = node->left;
//    }while(node != head);
//    return i;
//}
//
//int choosePC(Node *head){
//    int i = printAllThePCS(head);
//    int pcNumber;
//    do{
//        rewind(stdin);
//        printf("Choose PC from the list: ");
//    }while(!scanf("%d", &pcNumber) || pcNumber < 0 || pcNumber > i);
//    return pcNumber;
//}
//
//void switchPower(Node* head){
//    int ID = choosePC(head);
//    int i = 0;
//    while(i != ID){
//        head = head->left;
//        i++;
//    }
//    
//    if(head->pc.power == 0){
//        head->pc.power = 1;
//    }else{
//        head->pc.power = 0;
//    }
//}
//
//int tryPC(Node *node, int number){
//    printf("Trying PC [%d] with ID: %s", number, node->pc.ID);
//    if(!node->pc.power){
//        printf("No power!\n");
//    }
//    return node->pc.power;
//}
//
//int tryClockWise(Node *head, int firstID, int secondID){
//    Node* node = head;
//    
//    int numberOfNodes = 0;
//    do{
//        node = node->left;
//        numberOfNodes++;
//    }while(node != head);
//    
//    int i = 0;
//    
//    while(i != firstID){
//        node = node->left;
//        i++;
//    };
//    Node* firstNode = node;
//    
//    if(secondID > firstID && tryPC(node, i)){
//        do{
//            node = node->left;
//            if(!tryPC(node, i + 1)){
//                break;
//            }
//            i++;
//        }while(i != secondID);
//        
//        if(i != secondID){
//            i = firstID;
//            node = firstNode;
//            
//            if(!tryPC(node, i)){
//                printf("Cannot transmit data!\n");
//                return 0;
//            }
//            
//            while(i != 0){
//                node = node->right;
//                if(!tryPC(node, i - 1)){
//                    printf("Cannot transmit data!\n");
//                    return 0;
//                }
//                i--;
//            }
//            node = node->right;
//            i = numberOfNodes - 1;
//            
//            if(secondID == numberOfNodes - 1 && tryPC(node, numberOfNodes - 1)){
//                printf("Success!\n");
//                return 1;
//            }
//            
//            if(!tryPC(node, i)){
//                do{
//                    node = node->right;
//                    if(!tryPC(node, i - 1)){
//                        break;
//                    }
//                    i--;
//                }while(i != secondID);
//            }
//        }
//    }
//    
//    
//    if(secondID < firstID && tryPC(node, i)){
//        do{
//            node = node->right;
//            if(!tryPC(node, i - 1)){
//                break;
//            }
//            i--;
//        }while(i != secondID);
//        
//        if(i != secondID){
//            i = firstID;
//            node = firstNode;
//            
//            if(!tryPC(node, i)){
//                printf("Cannot transmit data!\n");
//                return 0;
//            }
//            
//            while(i != numberOfNodes - 1){
//                node = node->left;
//                if(!tryPC(node, i + 1)){
//                    printf("Cannot transmit data!\n");
//                    return 0;
//                }
//                i++;
//            }
//            node = node->left;
//            i = 0;
//            
//            if(secondID == 0 && tryPC(node, 0)){
//                printf("Success!\n");
//                return 1;
//            }
//            
//            if(tryPC(node, i)){
//                do{
//                    node = node->left;
//                    if(!tryPC(node, i + 1)){
//                        break;
//                    }
//                    i++;
//                }while(i != secondID);
//            }
//        }
//        
//    }
//    
//    
//    if(i == secondID){
//        printf("Success!\n");
//        return 1;
//    }else{
//        printf("Cannot transmit data!\n");
//        return 0;
//    }
//}
//
//int tryCounterWise(Node *head, int firstID, int secondID){
//return 0;
//
//}
//
//void sendData(Node *head, int firstID, int secondID){
//    printf("Trying to send...\n");
//    
//    int numberOfNodes = 0;
//    Node *node = head;
//    
//    do{
//        node = node->right;
//        numberOfNodes++;
//    }while(node != head);
//    
//    if(!tryClockWise(head, firstID, secondID)){
//        tryCounterWise(head, firstID, secondID);
//    }
//    
//    return;
//}
//
//int main(){
//    Node* head = NULL;
//    int temp;
//    do{
//        do{
//            printf("0: Add a PC\n1: Print all PCs\n2: Switch PC power\n3: Send data\n4: Exit\n");
//            rewind(stdin);
//        }while(!scanf("%d", &temp) || temp < 0 || temp > 4);
//        switch (temp) {
//            case 0:
//                add(&head, createPC());
//                break;
//            case 1:
//                if(!head){
//                    printf("No PCs\n");
//                    break;
//                }
//                printAllThePCS(head);
//                break;
//            case 2:
//                if(!head){
//                    printf("No PCs\n");
//                    break;
//                }
//                switchPower(head);
//                break;
//            case 3:
//                if(!head || head->left == head){
//                    printf("Not enough PCs\n");
//                    break;
//                }
//                
//                int a = choosePC(head);
//                int b = choosePC(head);
//                
//                while(b == a){
//                    printf("Cannot be sent from %d to %d\n", a, a);
//                    b = choosePC(head);
//                }
//                
//                sendData(head, a, b);
//                
//                break;
//        }
//    }while(temp != 4);
//}
