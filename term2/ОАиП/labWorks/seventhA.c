//
//  seventhA.c
//  labWorks
//
//  Created by Андрэй Гурыновіч on 5/20/20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

//1. Реализовать бинарное дерево поиска с целочисленными ключами, функцию добавления элементов с клавиатуры и вывода в прямом (pre-order) порядке. Вывести количество узлов с только одним потомком.
//Порядок pre-order для дерева A
///\ BC /\\
//DEF
//будет A B D E C F.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
}Node;

Node* createNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    return node;
}

void addNodeToTheTree(Node** root, Node* node){

    if(*root == NULL){
        *root = node;
        return;
    }

    if((*root)->key == node->key){
        printf("Node with this key %d already exist", node->key);
        return;
    }

    if(node-> key < (*root)->key){
        addNodeToTheTree(&(*root)->left, node);
    }else{
        addNodeToTheTree(&(*root)->right, node);
    }
}

void printTreeInPreOrderWay(Node* root){
    printf("%d ;", root->key);
    if(root->left != NULL){
        printTreeInPreOrderWay(root->left);
    }
    if(root->right != NULL){
        printTreeInPreOrderWay(root->right);
    }
}


int countNodeWithOneBranch(Node *root, int firstTime){
    static int count;
    if(firstTime){
        count = 0;
    }
    if(root->left != NULL){
        countNodeWithOneBranch(root->left, 0);
    }
    if(root->right != NULL){
        countNodeWithOneBranch(root->right, 0);
    }
    if((root->left && !root->right) || (!root->left && root->right)){
        count++;
    }
    return count;
}



int main(){
    Node* root = NULL;
    int temp;
    do{
        do{
            printf("0: Add a node\n1: Print in pre-order way\n2: Count number of nodes with one branch\n3: Exit\n");
            rewind(stdin);
        }while(!scanf("%d", &temp) || temp < 0 || temp > 3);

        if(temp == 3){
            return 0;
        }

        switch (temp) {
            case 0:
                do{
                    printf("Enter key: ");
                    rewind(stdin);
                }while(!scanf("%d", &temp));
                addNodeToTheTree(&root, createNode(temp));
                break;
            case 1:
                if(!root){
                    printf("No root\n");
                    break;
                }
                printTreeInPreOrderWay(root);
                printf("\n");
                break;
            case 2:
                if(!root){
                    printf("No root\n");
                    break;
                }
                printf("Number of nodes with only one branch: %d\n", countNodeWithOneBranch(root, 1));
                break;
        }
    }while(1);
}
