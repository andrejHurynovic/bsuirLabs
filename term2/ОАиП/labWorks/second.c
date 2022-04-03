////
////  second.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 2/17/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//
////6.
////1. Реализовать структуру, представляющую вложение к письму. Структура содержит тип вложения (текстовый документ, изображение) и объединение структур, представляющих каждый из типов вложения. Текстовый документ содержит кол-во страниц и первый абзац текста. Изображение - размер в пикселях и URL. Сделать возможность составить письмо с приложением, проверить, валидность приложения к письму. Письмо невалидно, если в текстовом документе приложения больше 10000 страниц или протокол в URL изображения - http, а не https.
////2. Добавить новый тип вложения - бинарный файл. Структура, представляющая бинарный файл содержит имя и поля бит: проверен ли на вирусы, больше ли максимального размера, из доверенного ли источника, исполняемый ли. Письмо невалидно, если бинарный файл не проверен на вирусы, больше максимального размера или не из доверенного источника. Добавить поиск по частичному совпадению текста во вложениях: внутри первого абзаца текста, в URL изображения, имени бинарного файла.
//
//
//
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
//
//int scanNumber(char* description){
//    int number;
//    printf("%s", description);
//    do{
//        rewind(stdin);
//    } while (!scanf("%d", &number));
//    return number;
//}
//
//
//
//
//
//
//
//enum Type{
//    textDocument,
//    image,
//    binaryFile
//};
//
//
//
//struct TextDocument{
//    int pages;
//    char* firstParagraph;
//};
//
//struct Image{
//    int height;
//    int width;
//    char* url;
//};
//
//struct BinaryFile{
//    char* ID;
//    unsigned int haveVirus: 1;
//    unsigned int biggerThenMaximalSize: 1;
//    unsigned int trustedSource: 1;
//    unsigned int executable: 1;
//};
//
//struct Attachment {
//    enum Type type;
//    union{
//        struct Image image;
//        struct TextDocument textDocument;
//        struct BinaryFile binaryFile;
//    };
//};
//
//struct Letter{
//    struct Attachment attachment;
//};
//
//
//
//
//struct TextDocument createTextDocument(){
//    struct TextDocument document;
//    do{
//        document.pages = scanNumber("\nEnter the number of pages: ");
//    }while(document.pages < 1);
//    document.firstParagraph = createAndScanString("Enter the first paragraph: ");
//    return document;
//};
//
//struct Image createImage(){
//    struct Image image;
//    do{
//        image.height = scanNumber("\nEnter the height of the image: ");
//    }while(image.height < 1);
//    do{
//        image.width = scanNumber("Enter the width of the image: ");
//    }while(image.width < 1);
//    image.url = createAndScanString("Enter the image URL: ");
//    return image;
//};
//
//struct BinaryFile createBinaryFile(){
//    struct BinaryFile file;
//    file.ID = createAndScanString("Enter file name: ");
//    unsigned int temp;
//    do{
//        temp = scanNumber("Is executable?(0/1): ");
//    }while(temp != 0 && temp != 1);
//    file.executable = temp;
//    do{
//        temp = scanNumber("Is infected?(0/1): ");
//    }while(temp != 0 && temp != 1);
//    file.haveVirus = temp;
//    do{
//        temp = scanNumber("Is it from trusted source?(0/1): ");
//    }while(temp != 0 && temp != 1);
//    file.trustedSource = temp;
//    do{
//        temp = scanNumber("Is it bigger then maximal size?(0/1): ");
//    }while(temp != 0 && temp != 1);
//    file.biggerThenMaximalSize = temp;
//    return file;
//};
//
//struct Letter createLetter(){
//    struct Letter letter;
//    do{
//        letter.attachment.type = scanNumber("0: Text document\n1: Image\n2: Binary file\n");
//    }while(letter.attachment.type < 0 || letter.attachment.type > 2);
//    switch (letter.attachment.type) {
//        case textDocument:
//            letter.attachment.textDocument = createTextDocument();
//            break;
//        case image:
//            letter.attachment.image = createImage();
//            break;
//        case binaryFile:
//            letter.attachment.binaryFile = createBinaryFile();
//            break;
//    }
//    return letter;
//}
//
//
//
//
//
//
//int validateImage(struct Image* image){
//    const int size = 5;
//    char validationString[size] = "https";
//    int temp = 0;
//    while(temp < size){
//        if(image->url[temp] != validationString[temp]){
//            return 0;
//        }
//        temp++;
//    }
//    return 1;
//}
//
//int validateDocument(struct TextDocument* document){
//    int maximalSize = 10000;
//    if(document->pages > maximalSize){
//        return 0;
//    }
//    return 1;
//}
//
//int validateBinaryFile(struct BinaryFile* file){
//    if(file->biggerThenMaximalSize || file->haveVirus || !file->trustedSource){
//        return 0;
//    } else {
//        return 1;
//    }
//}
//
//int ValidateLetter(struct Letter* letter){
//    switch (letter->attachment.type) {
//        case 0:
//            return validateDocument(&letter->attachment.textDocument);
//            break;
//        case image:
//            return validateImage(&letter->attachment.image);
//            break;
//        case binaryFile:
//            return validateBinaryFile(&letter->attachment.binaryFile);
//            break;
//    }
//}
//
//
//
//
//
//
//
//
//void ShowLetter(struct Letter* letter){
//    switch (letter->attachment.type) {
//        case textDocument:
//            printf("\nDocument type: text document");
//            printf("\nNumber of pages: %d", letter->attachment.textDocument.pages);
//            printf("\nFirst paragraph: %s\n", letter->attachment.textDocument.firstParagraph);
//            break;
//        case image:
//            printf("\nDocument type: image");
//            printf("\nHeight: %d", letter->attachment.image.height);
//            printf("\nWidth: %d", letter->attachment.image.width);
//            printf("\nURL: %s\n", letter->attachment.image.url);
//            break;
//        case binaryFile:
//            printf("\nDocument type: binary file");
//            printf("\nID: %s", letter->attachment.binaryFile.ID);
//            printf("\nExecutable: %d", letter->attachment.binaryFile.executable);
//            printf("\nFrom trusted source: %d", letter->attachment.binaryFile.trustedSource);
//            printf("\nHave a virus: %d", letter->attachment.binaryFile.haveVirus);
//            printf("\nBigger then maximal size: %d\n", letter->attachment.binaryFile.biggerThenMaximalSize);
//            break;
//    }
//}
//
//
//
//
//
//
//
//struct LettersVector{
//    struct Letter* letters;
//    int size;
//    int filled;
//};
//
//struct LettersVector CreateLettersVector(int size){
//    struct LettersVector lettersVector;
//    lettersVector.letters= (struct Letter*)malloc(sizeof(struct Letter) * size);
//    lettersVector.size = size;
//    lettersVector.filled = 0;
//    return lettersVector;
//}
//
//
//void AddLetterToVector(struct LettersVector* vector, struct Letter letter){
//    vector->letters[vector->filled] = letter;
//    vector->filled++;
//    if(vector->filled >= vector->size){
//        vector->size *=2;
//        vector->letters = (struct Letter*)realloc(vector->letters, sizeof(struct Letter) * vector->size);
//    }
//}
//
//
//
//void ValidateLetters(struct LettersVector* vector){
//    for(int i = 0; i < vector->filled; i++){
//        printf("\n#%d", i);
//        ShowLetter(&vector->letters[i]);
//        printf("Validation result: %d\n\n", ValidateLetter(&vector->letters[i]));
//    }
//}
//
//
//
//int compareStrings(char* string, char* search){
//    long stringLenght = strlen(string);
//    long searchLenght = strlen(search);
//    
//    if(searchLenght > stringLenght){
//        return 0;
//    }
//    
//    for(int i = 0; i <= stringLenght - searchLenght; i++){
//        for(int j = i; j < j + 4; j++){
//            if(string[j] != search[j - i]){
//                break;
//            }
//            if(j == i + searchLenght - 1){
//                return 1;
//            }
//        }
//    }
//    return 0;
//}
//
//
//
//void searchInLettersByString(struct LettersVector* vector, char* string){
//    for(int i = 0; i < vector->filled; i++){
//        switch (vector->letters[i].attachment.type) {
//            case textDocument:
//                if(!compareStrings(vector->letters[i].attachment.textDocument.firstParagraph, string)){
//                    continue;
//                }
//                break;
//            case image:
//                if(!compareStrings(vector->letters[i].attachment.image.url, string)){
//                    continue;
//                }
//                break;
//            case binaryFile:
//                if(!compareStrings(vector->letters[i].attachment.binaryFile.ID, string)){
//                    continue;
//                }
//                break;
//        }
//        ShowLetter(&vector->letters[i]);
//    }
//}
//
//
//
//int main(){
//    struct LettersVector vector = CreateLettersVector(4);
//    int temp;
//    do{
//        printf("0: Create letter\n1: Validate letters\n2: Search\n");
//        do{
//            temp = scanNumber("");
//        }while(temp < 0 || temp > 2);
//        switch (temp) {
//            case 0:
//                AddLetterToVector(&vector, createLetter());
//                break;
//            case 1:
//                if(!vector.filled){
//                    printf("No letters\n");
//                    break;
//                }
//                ValidateLetters(&vector);
//                break;
//            case 2:
//                if(!vector.filled){
//                    printf("No letters\n");
//                    break;
//                }
//                searchInLettersByString(&vector, createAndScanString("Enter search string: "));
//                printf("\n");
//                break;
//            default:
//                break;
//        }
//    }while(1);
//}
