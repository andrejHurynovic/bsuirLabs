//
//  terminal.c
//  Lections
//
//  Created by Андрэй Гурыновіч on 1/14/20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


// в командной строке вводится несколько строк.
// в рекурсивной функции для каждой строки выполнить
// реверсивный переворот последнего слова


//void recursReverseLastWord(char *string, int i){
//    static int wordFirstSymbalIndex;
//    char symbal;
//    if (string[i] == ' '){
//        wordFirstSymbalIndex = i + 1;                   // запоминаем позицию ' ' перед словом
//    }
//    if (string[i] != '\0'){                             // если не конец строки
//        symbal = string[i++];                           // чтение символа из строки
//        recursReverseLastWord(string, i);               // рекурсия
//    }
//    else {
//        return;                                         // строка окончена
//    }
//    printf("\n i = %d  firstWordSymbalIndex = %d", i, wordFirstSymbalIndex);
//    if (string[wordFirstSymbalIndex] != '\0') {
//        string[wordFirstSymbalIndex++] = symbal;        //реверс слова
//    }
//    if (i==1){
//        wordFirstSymbalIndex = 0;
//    }
//}

void reverseLastWordViewComandToolLine(int argc,char *argv[]){
    int i;
    for(i = 1; i < argc; i++){
        printf("\nBefore: %s", argv[i]);
        recursReverseLastWord(argv[i], 0);
        printf("\nAfter: %s", argv[i]);
    }
    puts("\n\n");
}



//=================================================================================
// в командной строке вводятся слова состоящие из чисел и знаков
// '+' и '-', например 1+39-5-8+23=?  44-2-13+99=?



int stringToInt(char *string){
    int i = 0, number, polarity;
    while (string[i] == ' '){
        i++;
    }
    if (!string[i]){
        printf("error, empty string");
    }
    polarity = (string[i] == '-') ? -1 : 1;
    if (string[i] == '+' || string[i] == '-'){
        i++;
    }

    for (number = 0; string[i] >= '0' && string[i] <= '9'; i++){
        number = 10 * number + (string[i] - '0');
    }
    return polarity * number;
}





void comandLineCalculator(int argv,char *argc[]){
    int numberLenght,i,j,result;
    char *string, operationType;
    for(i = 1; i < argv; i++){                                  // считывание очередного слова из ком. стр.
        result = numberLenght = 0;
        operationType = ' ';
        string = (char *)calloc(1,sizeof(char));                     // строка для одного символа
        
        for(j = 0; argc[i][j]; j++){                            // проход по выбранному слову
            switch(argc[i][j]){
               case '?': break;
                case '=':
                case '-':
                case '+':
                    if (operationType == ' '){
                        result = stringToInt(string);      // первичная сумма
                    }
                    if (operationType == '+') {
                        result += stringToInt(string);     // увеличение результата
                    }
                    if (operationType == '-') {
                        result -= stringToInt(string);     // уменьшение результата
                    }
                    free(string);
                    numberLenght = 0;
                    string = (char *)calloc(1, sizeof(char));
                    operationType = argc[i][j];                             // запоминаем знак  +  -
                    break;                                      // сброс числа букв для ввода нового слова
                default: numberLenght++;
                    string=(char *)realloc(string,(numberLenght + 1) * sizeof(char));    // строка увеличивается на 1 букву
                    string[numberLenght - 1] = argc[i][j];                        // введена буква
                    string[numberLenght] = '\0';
            }
        }
        printf("%s result: %d\n",argc[i],result);
    }
}

