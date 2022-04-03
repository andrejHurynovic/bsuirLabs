//
//  main.cpp
//  Labwork 6. Memory manager
//
//  Created by Andrej Hurynovič on 21.05.21.
//

#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

struct block {
    void* pointer;
    int size;
};

char memory[20];
int available = sizeof(memory);
int poolsCounter;
block pools[10];

void initialize(){
    pools[0].size = available;
    pools[0].pointer = &memory[0];
    poolsCounter = 1;
}

void** Malloc(int size){
    if (size > available){
        cout << "Not enough memory" << endl;
        exit(0);
    }
    
    pools[poolsCounter].pointer = pools[0].pointer;
    pools[poolsCounter].size = size;
    poolsCounter++;
    available -= size;
    pools[0].pointer = &memory[sizeof(memory) - available];
    pools[0].size -= size;
    
    return &pools[poolsCounter - 1].pointer;
}

void printMemory(){
    for (int i = 1; i < poolsCounter; i++) {
        char *temp = (char*)pools[i].pointer;
        for (int j = 0; j < pools[i].size; j++) {
            cout << setw(5) << (int)temp[j];
        }
    }
    for (int i = 0; i < available; i++) {
        cout << setw(5) << " ****";
    }
    std::cout << std::endl;
}

void deletePool(int index) {
    int deleteSize = pools[index].size;
    for (int i = index; i < poolsCounter - 1; i++){
        pools[i + 1].pointer = pools[i].pointer;
        pools[i] = pools[i + 1];
    }
    char* tempPointer = (char*)pools[0].pointer;
    pools[0].pointer = &tempPointer[-deleteSize];
}

void defrag(int index, block temp) {
    char *tempPointer = (char*)temp.pointer;
    int j = 0;
    for (;; j++){
        if (&memory[j] == tempPointer) {
            break;
        }
    }
    for (int i = 0; i < sizeof(memory) - (j  + temp.size); i++) {
        *(tempPointer + i) = *(tempPointer + temp.size + i);
    }
}

void Free(void **deletePart) {
    for (int i = 0; i < poolsCounter; i++){
        if (*deletePart == pools[i].pointer){
            block temp = pools[i];
            pools[0].size += pools[i].size;
            available += pools[i].size;
            deletePool(i);
            poolsCounter--;
            defrag(i, temp);
        }
    }
}



int main(){
    initialize();
    printMemory();
    int **number = (int**)Malloc(sizeof(int));
    **number = 256;
    printMemory();
    Free((void**)number);
    printMemory();
    int **anotherNumber = (int**)Malloc(sizeof(int));
    **anotherNumber = 15;
    printMemory();
    char **symbols = (char**)Malloc(sizeof(char) * 2);
    **symbols = '1';
    printMemory();
    Free((void**)anotherNumber);
    printMemory();
    Free((void**)symbols);
    double **dNumber = (double**)Malloc(sizeof(double));
    **dNumber = 1.123;
    printMemory();
    Free((void**)dNumber);
    anotherNumber = (int**)Malloc(sizeof(int)*3);
    **anotherNumber = 15;
    printMemory();
    symbols = (char**)Malloc(sizeof(char) * 3);
    **symbols = '1';
    printMemory();
    Free((void**)symbols);
    printMemory();
    Free((void**)anotherNumber);
    printMemory();
    dNumber = (double**)Malloc(sizeof(double));
    **dNumber = 1.000;

    printMemory();
    symbols = (char**)Malloc(sizeof(char) * 2);
    **symbols = '1';
    printMemory();
    Free((void**)symbols);
    printMemory();
    Free((void**)dNumber);
    printMemory();
    printMemory();
}
