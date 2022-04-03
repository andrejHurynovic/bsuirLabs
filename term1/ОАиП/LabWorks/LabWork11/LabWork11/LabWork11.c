//
//  main.c
//  LabWork11
//
//  Created by Андрэй Гурыновіч on 12/3/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

//Дан массив строк. Необходимо сформировать массив указателей на первые по алфавиту n слов из этих предложений. Память под массивы отводить динамически. Использовать указатели на функции.

#include <stdio.h>
#include <stdlib.h>

int scanNumberWithLabel(char* string){
    int number;
    do{
        printf("%s", string);
        rewind(stdin);
    }while(!scanf("%d", &number) || number < 1);
    return number;
}

char* createAndScanString(){
    int stringLenght = scanNumberWithLabel("Lenght of string: ");
    
    char *string = (char*)malloc(stringLenght);
    
    do{
        fflush(stdin);
        printf("String: ");
        gets(string);
    }while (string[stringLenght] != '\0');
    return string;
}




int main(){
    int (*scanNumber)(char* string) = scanNumberWithLabel;
    char* (*createString)(void) = createAndScanString;
    
    
    int stringsNumber = (*scanNumber)("Number of strings: ");
    
    char** strings = (char**)malloc(sizeof(char*) * stringsNumber);
    
    for(int i = 0; i < stringsNumber; i++){
        strings[i] = (*createString)();
    }
    
    int i;
    
    
    char* string = NULL;
    char *word = NULL;
    
    int firstWordIndex;
    int wordLenght;
    
    int wordsNumber = 0;
    char **words = (char **)malloc(wordsNumber * sizeof(char*));
    
    
    for(int temp = 0; temp < stringsNumber; temp++){
        string = strings[temp];
        
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
            if(wordLenght && (string[firstWordIndex] >= 'A' && string[firstWordIndex] <= 'Z') || (string[firstWordIndex] >= 'a' && string[firstWordIndex] <= 'z')){
                word = (char*)malloc(wordLenght * sizeof(char));
                for(int j = 0; j < wordLenght; j++){
                    word[j] = string[firstWordIndex + j];
                }
                word[wordLenght] = '\0';
                
                wordsNumber++;
                words = (char**)realloc(words, sizeof(char*) * wordsNumber);
                words[wordsNumber - 1] = word;
            }
        }
        
    }
    
    free(string);
    free(strings);
    
    if(!wordsNumber){
        printf("No words");
        return 0;
    }
    
    int tempNumber;
    int numberOfSortingWords;
    do{
        numberOfSortingWords = (*scanNumber)("Number of words to sort: ");
    } while (numberOfSortingWords > wordsNumber || numberOfSortingWords < 1);
    
    
    for(int i = 0; i < numberOfSortingWords; i++){
        tempNumber = i;
        for(int j = i; j < wordsNumber; j++){
            if(words[tempNumber][01] > words[j][0]){
                tempNumber = j;
            }
        }
        
        if(tempNumber != i){
            word = words[tempNumber];
            words[tempNumber] = words[i];
            words[i] = word;
        }
    }
    
    free(word);
    
    words = (char**)realloc(words, sizeof(char*) * numberOfSortingWords);
    
    for(int i = 0; i < numberOfSortingWords; i++){
        puts(words[i]);
    }
    
    free(words);

    
    return 0;
}
