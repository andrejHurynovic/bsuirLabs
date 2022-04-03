//
//  main.c
//  LabWork6
//
//  Created by Андрэй Гурыновіч on 11/12/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


void ScanIntMatrixWithLenghtHeight(int** matrix, int lenght, int height){
    int number;
    
    for(int v = 0; v < height; v++){
        for (int h = 0; h < lenght;){
            rewind(stdin);printf("matrix[%d][%d] = ", v, h);
            number = scanf("%d", &matrix[v][h]);
            if (number){
                h++;
            }
        }
    }
}
void PrintIntMatrix(int** matrix, int lenght, int height){
    for (int v = 0; v < height; v++){
        for (int h = 0; h < lenght; h++) {
            printf("%4d", matrix[v][h]);
        }
        printf("\n");
    }
    
}


int main() {
    int lenght = 2;
    int height = 2;
    
    
    int **matrix = (int **)malloc(height * sizeof(int*));
    for (int h = 0; h < height; h++){
        matrix[h] = (int *)malloc(lenght * sizeof(int));
    }
    
    ScanIntMatrixWithLenghtHeight(matrix, lenght, height);
    printf("\n");
    
    PrintIntMatrix(matrix, lenght, height);
    printf("\n");
    
    
    int *minimalPositiveNumberIndex = malloc(sizeof(int));
    int *maximalNegativeNumberIndex = malloc(sizeof(int));
    int havePositive = 0;
    int haveNegative = 0;
    
    for (int v = 0; v < height; v++){
        for (int h = 0; h < lenght; h++) {
            if (matrix[v][h] >= 0){
                if(!havePositive){
                    havePositive++;
                    minimalPositiveNumberIndex = &matrix[v][h];
                }
                if(matrix[v][h] <= *minimalPositiveNumberIndex){
                    minimalPositiveNumberIndex = &matrix[v][h];
                }
            } else {
                if(matrix[v][h] > *maximalNegativeNumberIndex){
                    maximalNegativeNumberIndex = &matrix[v][h];
                }
                if(!haveNegative){
                    haveNegative++;
                    maximalNegativeNumberIndex = &matrix[v][h];
                }
            }
        }
    }
    
    
    if(havePositive && haveNegative){
        printf("\n");
        printf("minimalPositiveNumber: %d", *minimalPositiveNumberIndex);
        printf("\n");
        printf("maximalNegativeNumber: %d", *maximalNegativeNumberIndex);
        printf("\n");
        
        
        
        int temp = *maximalNegativeNumberIndex;
        *maximalNegativeNumberIndex = *minimalPositiveNumberIndex;
        *minimalPositiveNumberIndex = temp;
        
        
        PrintIntMatrix(matrix, lenght, height);
        
    } else {
        printf("No both polarity\n");
    }
    return 0;
}
