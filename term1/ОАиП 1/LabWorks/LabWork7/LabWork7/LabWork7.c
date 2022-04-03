//
//  main.c
//  LabWork7
//
//  Created by Андрэй Гурыновіч on 11/13/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void ScanIntMatrixWithSize(int** matrix, int size){
    
    int number;
    
    for(int i = 0; i < size; i++){
        matrix[i][i] = 0;
    }
    
    for(int v = 0; v < size; v++){
        for (int h = v + 1; h < size;){
            rewind(stdin);printf("matrix[%d][%d] = ", v, h);
            number = scanf("%d", &matrix[v][h]);
            if (number && (matrix[v][h] >= 0 && matrix[v][h] <= 2)){
                switch (matrix[v][h]) {
                    case 0:
                        matrix[h][v] = 2;
                        break;
                    case 2:
                        matrix[h][v] = 0;
                        break;
                    default:
                        matrix[h][v] = matrix[v][h];;
                }
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

int main(){
    int size = 4;
    int **matrix = (int **)malloc(size * sizeof(int*));
    for (int h = 0; h < size; h++){
        matrix[h] = malloc(size * sizeof(int));
    }
    
    ScanIntMatrixWithSize(matrix, size);
    printf("\n");
    PrintIntMatrix(matrix, size, size);
    printf("\n");
    
    int victories = 0;
    int defeats = 0;
    int value;
    int teamsWhichHaveMoreVictoriesThenDefeats = 0;
    int haveATeamWhichWinMoreThenAHalfOfMatches = 0;
    
    
    printf("Teams without defeats numbers: ");
    
    for(int h = 0; h < size; h++){
        victories = 0;
        defeats = 0;
        for(int v = 0; v < size; v++){
            if (v == h){
                continue;
            }
            value = matrix[v][h];
            switch (value) {
                case 0:
                    defeats++;
                    break;
                case 2:
                    victories++;
                    break;
                default:
                    break;
            }
        }
        if(victories > defeats){
            teamsWhichHaveMoreVictoriesThenDefeats++;
        }
        if(defeats == 0){
            if(h == size - 1){
                printf("%d", h);
            }else{
                printf("%d, ", h);
            }
        }
        if(!haveATeamWhichWinMoreThenAHalfOfMatches && victories > (size - 1) / 2){
            haveATeamWhichWinMoreThenAHalfOfMatches = 1;
        }
    }
    printf("\n");
    printf("Number of teams which have more victories then defeats: %d", teamsWhichHaveMoreVictoriesThenDefeats);
    printf("\n");
    
    printf("Does at least one team have more victories then a half of matches: ");
    if (haveATeamWhichWinMoreThenAHalfOfMatches){
        printf("true ");
    }else{
        printf("false ");
    }
    printf("\n");
    return 0;
}
