//
//  seventhB.c
//  labWorks
//
//  Created by Андрэй Гурыновіч on 5/20/20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

//2. Реализовать бинарное дерево с целочисленными ключами, вывод элементов дерева, добавление нового элемента с клавиатуры, задавая ключ родительского элемента и сторону (левый или правый потомок). Вывести количество элементов на каждом уровне бинарного дерева, где корень - 0-й уровень, его потомки - 1-й уровень, их потомки - 2-й уровень и т.д.

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


int checkThisKey(Node* root, int key){
    if(root->key == key){
        return 1;
    }
    if(root->left){
        if(checkThisKey(root->left, key) == 1){
            return 1;
        }
    }
    if(root->right){
        if(checkThisKey(root->right, key) == 1){
            return 1;
        }
    }
    return 0;
}

Node* findThisKey(Node *root, int key){
    if(root->key == key){
        return root;
    }
    if(root->left){
        if(findThisKey(root->left, key)){
            return findThisKey(root->left, key);
        }
    }
    if(root->right){
        if(findThisKey(root->right, key)){
            return findThisKey(root->right, key);
        }
    }
    return NULL;
}

void addNodeToTheTreeByKeyAndSide(Node* root, Node* node, int side){
    if(side == 0){
        if(root->left){
            printf("This side is already in use");
            return;
        }else{
            root->left = node;
        }
    }else{
        if(root->right){
            printf("This side is already in use");
            return;
        }else{
            root->right = node;
        }
    }
}

void addNodeToTheTree(Node** root, Node* node){
    if(*root == NULL){
        *root = node;
        return;
    }
    
    if(checkThisKey(*root, node->key)){
        printf("This key is already exist!\n");
        return;
    }
    
    
    int temp;
    do{
        rewind(stdin);
        printf("Enter root ID: \n");
    }while(!scanf("%d", &temp));
    
    Node* tempRoot = findThisKey(*root, temp);
    if(tempRoot != NULL){
        do{
            rewind(stdin);
            printf("Choose side:\n0: Left\n1: Right\n");
        }while(!scanf("%d", &temp) || temp < 0 || temp > 1);
        addNodeToTheTreeByKeyAndSide(tempRoot, node, temp);
    }else{
        printf("This key does not exist");
    }
}

void printTreeInPreOrderWay(Node* root){
    printf("%d ", root->key);
    if(root->left != NULL){
        printTreeInPreOrderWay(root->left);
    }
    if(root->right != NULL){
        printTreeInPreOrderWay(root->right);
    }
}


int* countNumberOfElementsOnEachLevel(Node *root, int level){
    static int* array;
    if(level == 0){
        array = (int*)calloc(1, sizeof(int));
    }
    if(array[0] < level){
        array = (int*)realloc(array, level + 1);
        array[0]++;
        array[level] = 0;
    }
    if(root->left){
        countNumberOfElementsOnEachLevel(root->left, level + 1);
    }
    if(root->right){
        countNumberOfElementsOnEachLevel(root->right, level + 1);
    }
    
    array[level]++;
    return array;
}



int main(){
    Node* root = NULL;
    int temp;
    do{
        do{
            printf("0: Add a node\n1: Print in pre-order way\n2: Count number of nodes on every level\n3: Exit\n");
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
                int* array = countNumberOfElementsOnEachLevel(root, 0);
                printf("Level 0: 1\n");
                for(temp = 1; temp < array[0]; temp++){
                    printf("Level %d: %d\n", temp, array[temp]);
                }
                break;
        }
    }while(1);
}
