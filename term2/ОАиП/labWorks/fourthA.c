////
////  fourth.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 3/16/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"
//
//#define maxinmalStringLenght 256
//
//int scanNumber(char* description){
//    int number;
//    printf("%s", description);
//    do{
//        rewind(stdin);
//    } while (!scanf("%d", &number));
//    rewind(stdin);
//    return number;
//}
//
//char* createAndScanString(char* description){
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
////1. В бинарном файле хранятся товары, у которых есть название, цена, оценка и путь к текстовому файлу с детальным описанием. Каждому товару соответствует отдельный файл с детальным описанием. Вывести всю информацию (включая детальное описание) о товарах с оценкой больше M. Число M ввести с клавиатуры. Дополнительных коллекций не использовать.
//
//
//struct Product{
//    char name[maxinmalStringLenght];
//    int price;
//    int rate;
//    char textFileLink[maxinmalStringLenght];
//};
//
//struct Product createProduct(){
//    struct Product product;
//    printf("Enter name: ");;
//    fflush(stdin);
//    fgets(product.name, maxinmalStringLenght, stdin);
//    product.price = scanNumber("Enter price: ");
//    product.rate = scanNumber("Enter rate: ");
//    printf("Enter text file name: ");;
//    fflush(stdin);
//    fgets(product.textFileLink, maxinmalStringLenght, stdin);
//
//    FILE* file = fopen(product.textFileLink, "w");
//    char *string = createAndScanString("Enter discription: ");
//    fputs(string, file);
//
//    fclose(file);
//    return product;
//}
//
//void showProduct(struct Product product){
//    printf("\nName: %s", product.name);
//    printf("Price: %d", product.price);
//    printf("\nRate: %d", product.rate);
//    FILE* file = fopen(product.textFileLink, "r");
//    char string[maxinmalStringLenght];
//    printf("\nDescription:\n%s\n", fgets(string, maxinmalStringLenght, file));
//    fclose(file);
//}
//
//void writeProduct(FILE *file, struct Product product, long point){
//    fseek(file, point * sizeof(struct Product), SEEK_SET);
//    fwrite(&product, sizeof(product), 1, file);
//}
//
//struct Product reedProduct(FILE *file, long point){
//    struct Product product;
//    fseek(file, point * sizeof(struct Product), SEEK_SET);
//    fread(&product, sizeof(product), 1, file);
//    return product;
//}
//
//
//
//int main(){
//
//    FILE* file = fopen("fourth", "wb+");
//    if(file == NULL){
//        printf("Cannot open file.\n");
//        return 0;
//    }
//    
//    int numberOfProducts = 0;
//
//
//
//    int temp;
//    do{
//        printf("0: Create product\n1: Read product with special rate\n");
//        do{
//            temp = scanNumber("");
//        }while(temp < 0 || temp > 1);
//        switch (temp) {
//            case 0:
//                writeProduct(file, createProduct(), numberOfProducts++);
//                break;
//            case 1:
//                if(!numberOfProducts){
//                    printf("No products\n");
//                    break;
//                }
//                temp = scanNumber("Enter rate:");
//                for(int i = 0; i < numberOfProducts; i++){
//                    struct Product product = reedProduct(file, i);
//                    if(product.rate > temp){
//                        showProduct(product);
//                    }
//
//                }
//                break;
//        }
//    }while(1);
//}
