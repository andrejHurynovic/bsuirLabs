//
//  main.c
//  LabWork8
//
//  Created by Андрэй Гурыновіч on 11/25/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

char* createAndScanString(int stringLenght){
    char *string;
    char error = 0;
    do{
        if (!(string = (char *)malloc(stringLenght))){
            error = 1;
        }
    }while (error == 1);
    do{
        fflush(stdin);
        printf("String: ");
        gets(string);
    }while (string[stringLenght] != '\0');
    return string;
}

int main() {
    int stringLenght;
    int withError;
    do{
        printf("String lenght: ");
        rewind(stdin);
        withError = scanf("%d", &stringLenght);
    }while (!withError || stringLenght < 1);
    
    char* string = createAndScanString(stringLenght);
    
    int i = 0;
    while (string[i] == ' ') {
        stringLenght--;
        i++;
    }
    
    for(int j = 0; j < stringLenght; j++){
        string[j] = string[j + i];
    }
    
    i = stringLenght - 1;
    while (string[i] == ' ') {
        i--;
        stringLenght--;
    }
    string[stringLenght] = '\0';
    
    i = 1;
    int temp;
    while(i < stringLenght - 1){
        if(string[i] == ' ' && string[i + 1] == ' '){
            temp = 0;
            while (string[i + 1 + temp] == ' ') {
                temp++;
            }
            stringLenght -= temp;
            for (int j = i; j < stringLenght; j++){
                string[j] = string[j + temp];
            }
        }
        i++;
    }
    
    string[stringLenght] = '\0';
    
    string = (char* )realloc(string, stringLenght);
    printf("Result:%s\n", string);
    
    free(string);
    
    return 0;
}
