////
////  lessonTwo.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 3/10/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//
//
//
//void func(FILE* file, char a, char b){
//    long int position;
//    char temp;
//    do{
//        if(fgetc(file) == a){
//            position = ftell(file);
//            fseek(file, -1, SEEK_END);
//            do{
//                temp = fgetc(file);
//                fputc(temp, file);
//                fseek(file, -3, SEEK_CUR);
//            }while(ftell(file) != position);
//        }
//        temp = fgetc(file);
//        fputc(temp, file);
//        fseek(file, -2, SEEK_CUR);
//        fputc(b, file);
//        fseek(file, 1, SEEK_CUR);
//    }while(feof(file));
//}
//
//
//
//int main(){
//    FILE* file = fopen("/Users/andrejgurinovic/Library/Mobile\ Documents/com\~apple\~CloudDocs/BSUIR/ОАиП/secondTerm/labWorks/tempFile", "r+");
//
//    func(file, 'a', 'b');
//    
//    //r+
//    //w+
//    //q+
//    //Всё смещает указатель на следующий элемент
//    //    fprintf(<#FILE *restrict#>, <#const char *restrict, ...#>);
//    //    fscanf(<#FILE *restrict#>, <#const char *restrict, ...#>);
//    //    fputs(<#const char *restrict#>, <#FILE *restrict#>);
//    //    fgets(<#char *restrict#>, <#int#>, <#FILE *#>);
//    //    getc(<#FILE *#>);
//    //    putc(<#int#>, <#FILE *#>);
//    
//    //    fseek(<#FILE *#>, <#long#>, SEEK_CUR);
//    //    ftell(<#FILE *#>);
//    //    fsetpos(<#FILE *#>, <#const fpos_t *#>);
//    //    fgetpos(<#FILE *restrict#>, <#fpos_t *#>);
//    
//    //    fflush(file);
//    
//    //    feof(file);
//    
//    
//    
//    
//}
