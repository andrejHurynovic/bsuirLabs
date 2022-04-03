//
//  main.c
//  LabWork4
//
//  Created by Андрэй Гурыновіч on 11/12/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>

void ScanIntArrayWithLenght(int array[], int lenght){
    int i = 0;
    int number;
    while (i < lenght) {
        rewind(stdin);
        printf("array[%d] = ", i);
        number = scanf("%d", &array[i]);
        if (number) i++;
    }
}

void PrintIntArray(int array[], int lenght){
    for (int i = 0; i < lenght; i++)
        printf("%4d", array[i]);
        printf("\n");
}


int main() {
    const int lenght = 10;
    int array[lenght];
    ScanIntArrayWithLenght(array, lenght);
    PrintIntArray(array, lenght);
    
    
    int minimalElement = 0;
    for(int i = 0; i < 5; i++){
        minimalElement = 0;
        for(int j = 0; j < lenght - i; j++){
            if (array[minimalElement] > array[j]){
                minimalElement = j;
            }
        }
        
        for(; minimalElement < lenght - 1 - i; minimalElement++){
            array[minimalElement] = array[minimalElement + 1];
        }
//        array[minimalElement] = 0;
        PrintIntArray(array, lenght - i - 1);
    }
    return 0;
}
