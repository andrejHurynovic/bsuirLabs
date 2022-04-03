//
//  sixthA.c
//  labWorks
//
//  Created by Андрэй Гурыновіч on 4/21/20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

//1. Реализовать очередь целочисленных значений, функции push_back, pop_front. Удалить из очереди N-й элемент, используя только данные функции и дополнительную очередь.

struct Node{
    int value;
    struct Node *next;
};

struct Queue{
    struct Node* tail;
    struct Node* head;
};

struct Queue InitQueue(){
    struct Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}

void Push(struct Queue *queue, int value){
    struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));
    tempNode->next = NULL;
    tempNode->value = value;
    
    if(queue->tail == NULL){
        queue->head = tempNode;
        queue->tail = tempNode;
        return;
    }
    
    queue->tail->next = tempNode;
    queue->tail = tempNode;
}

int Pop(struct Queue *queue){
    struct Node *tempNode = queue->head;
    
    
    queue->head = queue->head->next;
    if(queue->head == NULL){
        queue->tail = NULL;
    }
    int tempValue = tempNode->value;
    free(tempNode);
    return tempValue;
}

void PrintQueue(struct Queue *queue){
    if(queue->tail == NULL){
        printf("\nNo queue");
        return;
    }
    struct Node *tempNode;
    tempNode = queue->head;
    printf("\nQueue: \n");
    do{
        printf("%d\n", tempNode->value);
        tempNode = tempNode->next;
    }while(tempNode != NULL);
}

struct Queue* RemoveOnIndex(struct Queue *queue){
    
    if(queue->tail == NULL){
        printf("\nNo queue");
        return NULL;
    }
    
    struct Node *tempNode;
    tempNode = queue->head;
    
    if(queue->head == queue->tail){
        queue->head = NULL;
        queue->tail = NULL;
        return NULL;
    }
    
    
    int index;
    do{
        printf("\nEnter index: ");
        rewind(stdin);
    }while(!scanf("%d", &index) || index < 0);
    
    int temp = 0;
    
    while(tempNode->next != NULL && temp != index){
        tempNode = tempNode->next;
        temp++;
    }
    if(temp != index){
        printf("\nNo such index\n");
        return NULL;
    }else{
        struct Queue *newQueue = (struct Queue*)malloc(sizeof(struct Queue));
        newQueue->tail = NULL;
        temp = 0;
        do{
            if(temp == index){
                temp++;
                Pop(queue);
                continue;
            }
            Push(newQueue, Pop(queue));
            temp++;
        }while(queue->tail != NULL);
        return newQueue;
    }
}


int main(){
    struct Queue queue = InitQueue();
    int temp;
    do{
        do{
            printf("\n0: Push\n1: Print\n2: Remove\n");
            rewind(stdin);
        }while(!scanf("%d", &temp) || temp < 0 || temp > 2);
        switch (temp) {
            case 0:
                do{
                    printf("\nEnter number: ");
                    rewind(stdin);
                }while(!scanf("%d", &temp));
                Push(&queue, temp);
                break;
            case 1:
                PrintQueue(&queue);
                break;
            case 2:{
                struct Queue* tempQueue = RemoveOnIndex(&queue);
                if(tempQueue != NULL){
                    queue = *tempQueue;
                }
                free(tempQueue);
                break;
            }
        }
    }while (1);
}
