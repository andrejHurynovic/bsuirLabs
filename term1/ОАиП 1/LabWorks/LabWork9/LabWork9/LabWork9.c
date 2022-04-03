//
//  main.c
//  LabWork9
//
//  Created by Андрэй Гурыновіч on 11/26/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

char* createAndScanString(){
    char *string;
    int stringLenght;
    do{
        printf("String lenght: ");
        rewind(stdin);
        scanf("%d", &stringLenght);
    }while (stringLenght < 1);
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
    int strngsNumber;
    do{
        printf("strngsNumber: ");
        rewind(stdin);
    }while(!scanf("%d", &strngsNumber) || strngsNumber < 1);
    
    char** strings = (char**)malloc(sizeof(char*) * strngsNumber);
    char* string = NULL;
    
    for(int i = 0; i < strngsNumber; i++){
        strings[i] = createAndScanString();
    }
    
    
    int i;
    
    int firstWordIndex = 0;
    int wordLenght = 0;
    
    int wordNumber = 0;
    char **words = (char **)malloc(wordNumber * sizeof(char*));
    int *wordLenghts = (int *)malloc(wordNumber * sizeof(int));
    char *word = NULL;
    
    for (strngsNumber -= 1; strngsNumber >= 0; strngsNumber--){
        string = strings[strngsNumber];
        i = 0;
        while(string[i] != '\0'){
            wordLenght = 0;
            while(string[i] == ' '){
                i++;
            }
            if(string[i] != '\0'){
                firstWordIndex = i;
            }
            while(string[i] != ' ' && string[i] != '\0'){
                wordLenght++;
                i++;
            }
            if(wordLenght){
                word = (char*)malloc(wordLenght * sizeof(char));
                for(int j = 0; j < wordLenght; j++){
                    word[j] = string[firstWordIndex + j];
                }
                word[wordLenght] = '\0';
                
                wordNumber++;
                words = (char**)realloc(words, sizeof(char*) * wordNumber);
                words[wordNumber - 1] = word;
                wordLenghts = (int *)realloc(wordLenghts, wordNumber * sizeof(int));
                wordLenghts[wordNumber - 1] = wordLenght;
            }
        }
    }
    
    
    free(string);
    free(strings);
    
    int tempLength;
    int minimalIndex;
    for(i = 0; i < wordNumber - 1; i++){
        minimalIndex = i;
        for(int j = i; j < wordNumber; j++){
            if(wordLenghts[minimalIndex] > wordLenghts[j]){
                minimalIndex = j;
            }
        }
        if (minimalIndex == i){
            continue;
        }
        
        word = words[minimalIndex];
        words[minimalIndex] = words[i];
        words[i] = word;
        
        tempLength = wordLenghts[minimalIndex];
        wordLenghts[minimalIndex] = wordLenghts[i];
        wordLenghts[i] = tempLength;
    }
    
    free(wordLenghts);
    free(word);
    
    for(int j = 0; j < wordNumber; j++){
        printf("\n%s",words[j]);
    }
    
    free(words);
    
    return 0;
}
