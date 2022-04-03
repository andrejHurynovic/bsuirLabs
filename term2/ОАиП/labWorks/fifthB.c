////
////  fifthB.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 4/13/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//char* createAndScanString(char* description){
//    int maxinmalStringLenght = 256;
//    char *string;
//    char error;
//    do{
//        error = 0;
//        if (!(string = (char *)malloc(maxinmalStringLenght))){
//            error = 1;
//        }
//    }while (error == 1);
//    printf("%s", description);
//    rewind(stdin);
//    fgets(string, maxinmalStringLenght, stdin);
//    unsigned long lenght = strlen(string);
//    if(lenght < maxinmalStringLenght - 1){
//        string = (char*)realloc(string, maxinmalStringLenght - lenght);
//        string[lenght - 1] = '\0';
//    }
//    return string;
//}
//
////2. Реализовать эмуляцию текстового редактора с двумя функциями: добавить текст в конец, удалить текст между двумя индексами. Реализовать undo стек, который позволит отменять любое количество этих операций.
//
//struct UndoRemove{
//    int point;
//    int lenght;
//    char* symbols;
//};
//
//struct UndoWrite{
//    long lenght;
//};
//
//union Action{
//    struct UndoRemove remove;
//    struct UndoWrite write;
//};
//
//enum ActionType{
//    undoRemove, undoWrite
//};
//
//struct UndoNode{
//    union Action action;
//    enum ActionType type;
//    struct UndoNode* previous;
//};
//
//struct UndoStack{
//    struct UndoNode* last;
//};
//
//struct UndoStack initUndoStack(){
//    struct UndoStack stack;
//    stack.last = NULL;
//    return stack;
//}
//
//void pushIntoStack(struct UndoStack* stack, struct UndoNode* node){
//    node->previous = stack->last;
//    stack->last = node;
//}
//
//struct UndoNode* popFromStack(struct UndoStack* stack){
//    struct UndoNode* node = stack->last;
//    stack->last = stack->last->previous;
//    return node;
//}
//
//
//
//struct Range{
//    int a, b;
//};
//
//struct Range initRange(int a, int b){
//    struct Range range;
//    range.a = a;
//    range.b = b;
//    return range;
//}
//
//
//
//void removeSymbolsFromString(char* string, struct Range range, struct UndoStack *undoStack){
//
//    int temp = range.a;
//    int offset = range.b - range.a + 1;
//
//    struct UndoRemove undo;
//    undo.point = range.a;
//    undo.lenght = offset;
//    undo.symbols = (char*)malloc(undo.lenght);
//
//    while(string[temp] != '\0'){
//        if(temp < range.b + 1){
//            undo.symbols[temp - range.a] = string[temp];
//        }
//        if(string[temp+offset] != '\0'){
//        string[temp] = string[temp + offset];
//        }
//        temp++;
//    }
//
//    long lenght = strlen(string);
//    string = (char*)realloc(string, lenght - offset + 1);
//    string[lenght - offset] = '\0';
//
//    struct UndoNode *undoNode = (struct UndoNode*)malloc(sizeof(struct UndoNode));
//    undoNode->action.remove = undo;
//    undoNode->type = undoRemove;
//    undoNode->previous = NULL;
//
//    pushIntoStack(undoStack, undoNode);
//    free(undoNode);
//}
//
//void undoForRemove(char* string, struct UndoRemove undo){
//    long lenght = strlen(string);
//    lenght += undo.lenght;
//    string = (char*)realloc(string, lenght + 1);
//
//    string[lenght] = '\0';
//    
//    do{
//        string[lenght] = string[lenght - undo.lenght];
//        lenght--;
//    }while(lenght - undo.lenght != undo.point - 1);
//
//    for (int i = undo.point; i < undo.point + undo.lenght; i++) {
//        string[i] = undo.symbols[i - undo.point];
//    }
//}
//
//
//
//void addSymbolsToString(char** string, struct UndoStack *undoStack){
//    if(!*string){
//        *string = (char*)malloc(1);
//    }
//    long lenght = strlen(*string);
//
//    char* tempString = createAndScanString("Enter new symbols: ");
//    long tempLenght = strlen(tempString);
//    if(!tempLenght){
//        printf("No new symbols\n");
//        return;
//    }
//    int temp = 0;
//    *string = (char*)realloc(*string, lenght + tempLenght);
//    do{
//        string[0][lenght + temp] = tempString[temp];
//        temp++;
//    }while(temp <= tempLenght);
//
//    struct UndoWrite undo;
//    undo.lenght = tempLenght;
//
//    struct UndoNode *undoNode = (struct UndoNode*)malloc(sizeof(struct UndoNode));
//    undoNode->action.write = undo;
//    undoNode->type = undoWrite;
//    undoNode->previous = NULL;
//
//    pushIntoStack(undoStack, undoNode);
//}
//
//void undoForWrite(char* string, struct UndoWrite undo){
//    long lenght = strlen(string);
//    lenght -= undo.lenght;
//    string = (char*)realloc(string, lenght + 1);
//    string[lenght] = '\0';
//}
//
//
//
//int main(){
//    int temp;
//    char* string = NULL;
//    struct UndoStack undoStack = initUndoStack();
//    do{
//        do{
//            printf("0: Add symbols\n1: Print string\n2: Remove symbols from string in range\n3: Undo\n");
//            rewind(stdin);
//        }while(!scanf("%d", &temp) || temp < 0 || temp > 3);
//        switch (temp) {
//            case 0:
//                addSymbolsToString(&string, &undoStack);
//                break;
//            case 1:
//                if(!string || !strlen(string)){
//                    printf("No symbols\n");
//                    break;
//                }
//                puts(string);
//                break;
//            case 2:
//            {
//                long lenght;
//                if(string){
//                    lenght = strlen(string);
//                    if(!lenght){
//                        printf("No symbols\n");
//                        break;
//                    }
//                }else{
//                    printf("No symbols\n");
//                    break;
//                }
//                int a;
//                int b;
//                do{
//                    printf("Enter first range point: ");
//                }while(!scanf("%d", &a) || a < 0 || a > lenght);
//                do{
//                    printf("Enter second range point: ");
//                    rewind(stdin);
//                }while(!scanf("%d", &b) || b < a || b > lenght);
//                removeSymbolsFromString(string, initRange(a, b), &undoStack);
//                break;
//            }
//            case 3:
//                if(!undoStack.last || !string){
//                    printf("No undo now\n");
//                    break;
//                }
//                struct UndoNode undo = *popFromStack(&undoStack);
//                if(undo.type == undoRemove){
//                    undoForRemove(string, undo.action.remove);
//                }else{
//                    undoForWrite(string, undo.action.write);
//                }
//                break;
//        }
//
//    }while(1);
//}
