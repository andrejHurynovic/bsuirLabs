//
//  main.c
//  LabWork10
//
//  Created by Андрэй Гурыновіч on 12/3/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

//Дана действительная квадратная матрица порядка n. Построить последовательность действительных чисел a1,...an по правилу: если в i-ой строке матрицы элемент, принадлежащий главной диагонали, отрицателен, то ai равно сумме элементов i-ой строки, предшествующих первому отрицательному элементу, иначе ai равно сумме последних элементов i-ой строки, начиная по порядку с неотрицательного элемента. Память под массивы отводить динамически. Программу разбить на функции.


#include <stdio.h>
#include <stdlib.h>

int scanIntNumber(){
    int number;
    do{
        rewind(stdin);
    }while(!(scanf("%d", &number)) || number <= 0);
    return number;
}

int** CreateIntMatrixWithSize(int size){
    int **matrix = (int**)malloc(size * sizeof(int*));
    for (int row = 0; row < size; row++){
        matrix[row] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

void ScanIntMatrixWithSize(int** matrix, int size){
    for(int row = 0; row < size; row++){
        for (int column = 0; column < size;){
            rewind(stdin);
            printf("matrix[%d][%d] = ", row, column);
            if(scanf("%d", &matrix[row][column])){
                column++;
            }
        }
    }
}

void PrintIntMatrixWithSize(int** matrix, int size){
    for (int row = 0; row < size; row++){
        for (int column = 0; column < size; column++) {
            printf("%4d", matrix[row][column]);
        }
        printf("\n");
    }
}

int* CreateIntArrayWithSize(int size){
    int* array = calloc(size, sizeof(int));
    return array;
}

void PrintIntArrayWithSize(int* array, int size){
    for(int i = 0; i < size; i++){
        printf("%4d", array[i]);
    }
}

int IsIntPositive(int number){
    if(number >= 0){
        return 1;
    } else {
        return 0;
    }
}

int main() {
    printf("Enter matrix size: ");
    int size = scanIntNumber();
    
    int** matrix = CreateIntMatrixWithSize(size);
    
    ScanIntMatrixWithSize(matrix, size);
    PrintIntMatrixWithSize(matrix, size);
    
    int* array = CreateIntArrayWithSize(size);
    
    
    for(int row = 0; row < size; row++){
        if (IsIntPositive(matrix[row][row])){
            int i = size - 1;
            while(!IsIntPositive(matrix[row][i])){
                i--;
            }
            while(i >= 0){
                array[row] += matrix[row][i];
                i--;
            }
            
        } else {
            for(int i = 0; i < size; i++){
                if(IsIntPositive(matrix[row][i])){
                    array[row] += matrix[row][i];
                } else {
                    break;
                }
            }
        }
    }
    
    free(matrix);
    puts("Result:");
    PrintIntArrayWithSize(array,size);
    
    free(array);
    
    return 0;
}
