//
//  matrix.c
//  Matrix
//
//  Created by Андрэй Гурыновіч on 11/3/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include<stdio.h>
#include <stdlib.h>


int** createMatrix(int rows, int columns){
    
    int** matrix = (int**)malloc(sizeof(int*) * rows);
    
    for(int row = 0; row < rows; row++){
        matrix[row] = (int*)malloc(sizeof(int) * columns);
    }
    return matrix;
}

void scanMatrix(int **matrix, int rows, int columns){
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            do{
                rewind(stdin);
                printf("matrix[%d][%d] = ", row, column);
            }while(!scanf("%d", &matrix[row][column]));
        }
    }
}

void printMatrix(int **matrix, int rows, int columns){
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            printf("%4d", matrix[row][column]);
        }
        printf("\n");
    }
}


void TransposeMatrixAcorssMainDiagonal(int** matrix, int size){
    int temp;
    for(int row = size - 1 ; row > 0; row--){
        for(int column = 0; column <row; column++){
            temp = matrix[row][column];
            matrix[row][column] = matrix[column][row];
            matrix[column][row] = temp;
        }
    }
}

int minimalInThisRowIndex;
int maximalInThisColumnIndex;

void findSedleElement(int **matrix, int rows, int columns){
    for(int i = 0; i < rows; i++){
        minimalInThisRowIndex = 0;
        for(int column = 1; column < columns; column++){
            if(matrix[i][minimalInThisRowIndex] > matrix[i][column]){
                minimalInThisRowIndex = column;
            }
        }
        maximalInThisColumnIndex = 0;
        for(int row = 1; row < rows; row++){
            if(matrix[row][minimalInThisRowIndex] > matrix[maximalInThisColumnIndex][minimalInThisRowIndex]){
                maximalInThisColumnIndex = row;
            }
        }
        if(i == maximalInThisColumnIndex){
            printf("matrix[%d][%d] = %d\n", i, minimalInThisRowIndex, matrix[i][minimalInThisRowIndex]);
        }
    }
}



void sortAboveMainDiaglonal(int** matrix, int size){
    int lenght = 0;
    for (int i = size - 1; i > 0; i--){
        lenght += i;
    }
    
    int index = 0;
    int** array = (int**)malloc(sizeof(int*) * lenght);
    for(int row = 0; row < size - 1; row++){
        for(int column = row + 1; column < size; column++){
            array[index++] = &matrix[row][column];
        }
    }
    
    int minimalIndex;
    int temp;
    for(int i = 0; i < lenght; i++){
        minimalIndex = i;
        for(int j = i; j < lenght; j++){
            if(*array[minimalIndex] > *array[j]){
                minimalIndex = j;
            }
        }
        temp = *array[minimalIndex];
        *array[minimalIndex] = *array[i];
        *array[i] = temp;
    }
}

void FindMinimalAndMaximalColumnSumUnderAndAboveMainDiagonal(int** matrix, int size){
    
    int tempSum;
    int minimalSum = matrix[size - 1][size - 2];
    int maximalSum = matrix[0][1];
    int mixColumnIndex = size - 2;
    int maxColumnIndex = 1;

    
    for(int column = 0; column < size; column++){
        tempSum = 0;
        for(int row = 0; row < column; row++){
            tempSum += matrix[row][column];
        }
        if(maximalSum < tempSum){
            maximalSum = tempSum;
            maxColumnIndex = column;
        }
        if(column == size - 1){
            break;
        }
        tempSum = 0;
        for(int row = column + 1; row < size; row++){
            tempSum += matrix[row][column];
        }
        if(minimalSum > tempSum){
            minimalSum = tempSum;
            mixColumnIndex = column;
        }
    }
    printf("maximalIndex: %d, with number: %d\n, minimalIndex: %d, with number: %d\n", maxColumnIndex, maximalSum, mixColumnIndex, minimalSum);
    
}




int main(){
    int rows = 3;
    int columns = 3;
    int** firstMatix = createMatrix(rows - 1, columns);
    int** secondMatrix = createMatrix(rows, columns - 1);
    scanMatrix(firstMatix, rows, columns - 1);
    scanMatrix(secondMatrix, rows - 1, columns);
    
    int** resultMatrix = createMatrix(rows - 1, columns - 1);

    for(int i = 0; i < rows - 1; i++){
        for(int j = 0; j < columns -1; j++){
            for(int l = 0; l < rows; l++){
                resultMatrix[i][j] += firstMatix[i][l] * secondMatrix[l][j];
            }
        }
    }
    
}
