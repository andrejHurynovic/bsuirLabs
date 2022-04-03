//
////  third.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 3/13/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//
//
//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"
//#include "unistd.h"
//
//char* createAndScanString(char* description){
//    int maxinmalStringLenght = 129;
//    char *string;
//    char error;
//    do{
//        error = 0;
//        if (!(string = (char *)malloc(maxinmalStringLenght))){
//            error = 1;
//        }
//    }while (error == 1);
//    printf("%s", description);
//    rewind(stdin);
//    fgets(string, maxinmalStringLenght, stdin);
//    unsigned long lenght = strlen(string);
//    if(lenght < maxinmalStringLenght - 1){
//        string = (char*)realloc(string, maxinmalStringLenght - lenght);
//        string[lenght - 1] = '\0';
//    }
//    return string;
//}
//
////1. Инвертировать текстовый файл без использования дополнительных массивов и файлов.
////2. Дан текстовый файл. С клавиатуры ввести слово. В файле удалить каждое слово, находящееся перед введенным словом. Дополнительных файлов и коллекций не использовать.
//
//void flipOverFile(FILE* file){
//    long int lenght;
//    char tempA;
//    char tempB;
//
//    fseek(file, 0, SEEK_END);
//    lenght = ftell(file);
//
//    for(int i = 0; i < lenght/2; i++){
//        fseek(file, 0 + i, SEEK_SET);
//        tempA = fgetc(file);
//
//        fseek(file, -1 - i, SEEK_END);
//        tempB = fgetc(file);
//
//        fseek(file, -1 , SEEK_CUR);
//        fputc(tempA, file);
//        fflush(file);
//
//        fseek(file, 0 + i, SEEK_SET);
//        fputc(tempB, file);
//        fflush(file);
//    }
//}
//
//
//
//void deleteAllBeforeThisWord(FILE* file, char* search){
//    fseek(file, 0, SEEK_END);
//    long int fileLenght = ftell(file);
//
//    int temp;
//    long searchLenght = strlen(search);
//    char c = 0;
//
//    for(int i = 1; i <= fileLenght; i++){
//        fseek(file, i, SEEK_SET);
//        if(fgetc(file) != ' '){
//            continue;
//        }
//
//        temp = 0;
//        while(fgetc(file) == search[temp]){
//            temp++;
//            if(temp == searchLenght){
//                if(ftell(file) != fileLenght){
//                    if(getc(file) != ' '){
//                        break;
//                    }
//                }
//
//                temp = 0;
//                while(c != ' '){
//                    fseek(file, i - 1 - temp, SEEK_SET);
//                    c = fgetc(file);
//                    temp++;
//                    if((ftell(file) - 1) == 0){
//                        temp++;
//                        break;
//                    }
//                };
//                ;
//
//                fseek(file, i + 1, SEEK_SET);
//
//                while(ftell(file) != fileLenght){
//                    c = getc(file);
//                    fseek(file, -(temp + 1), SEEK_CUR);
//                    putc(c, file);
//                    fflush(file);
//                    fseek(file, temp, SEEK_CUR);
//                }
//                fileLenght -= temp;
//                ftruncate(fileno(file), fileLenght);
//                i--;
//            }
//        }
//    }
//}
//
//
//
//int main(){
//    FILE *file = fopen("/Users/andrejgurinovic/Library/Mobile\ Documents/com\~apple\~CloudDocs/BSUIR/ОАиП/secondTerm/labWorks/third", "r+");
//    if(file == NULL){
//        printf("Cannot open file.\n");
//        return 0;
//    }
//    deleteAllBeforeThisWord(file, createAndScanString("Scan search string: "));
//    fclose(file);
//}
