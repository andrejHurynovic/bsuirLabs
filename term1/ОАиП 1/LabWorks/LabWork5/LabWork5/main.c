//
//  main.c
//  LabWork5
//
//  Created by Андрэй Гурыновіч on 11/12/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

//Отсортировать строки массива А размером n*m по убыванию.

#include <stdio.h>
#include <stdlib.h>


void ScanIntMatrixWithLenghtHeight(int** matrix, int lenght, int height){
    int number;
    
    for(int v = 0; v < height; v++){
        for (int h =0; h < lenght;){
            rewind(stdin);
            printf("matrix[%d][%d] = ", v, h);
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
    int lenght = 3;
    int height = 4;
    
    int** matrix = (int **)malloc(height * sizeof(int*));
    for (int h = 0; h < height; h++){
        matrix[h] = (int *)malloc(lenght * sizeof(int));
    }
    ScanIntMatrixWithLenghtHeight(matrix, lenght, height);
    PrintIntMatrix(matrix, lenght, height);
    printf("\n");
    
    
    int minimalElemetIndex, temp;
    
    for (int i = 0; i < lenght; i++){
        for (int k = height - 1; k >= 0; k--){
            minimalElemetIndex = k;
            
            for (int j = k; j >= 0; j--){
                if(matrix[minimalElemetIndex][i] > matrix[j][i]){
                    minimalElemetIndex = j;
                }
            }
            
            temp = matrix[minimalElemetIndex][i];
            matrix[minimalElemetIndex][i] = matrix[k][i];
            matrix[k][i] = temp;
        }
    }
    PrintIntMatrix(matrix, lenght, height);
    return 0;
}
