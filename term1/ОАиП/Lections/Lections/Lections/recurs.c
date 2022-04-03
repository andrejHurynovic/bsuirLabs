//
//  recurs.c
//  Recurs
//
//  Created by Андрэй Гурыновіч on 11/14/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>



int factorialFirst(int number){
    if(number == 1 || number == 0){
        return 1;
    } else {
        return number * factorialFirst(number - 1);
    }
}



//static сохраняет своё значение между функциями, точнее их итерациями
int factorialSecond(int number){
    static int i = 0;                                       // i-статическая переменная, чтобы сохранять своё последнее
                                                    // значение при каждом новом вызове функции
    int factorial;
    if (number <= 1)                                // если число = 0 или 1
        return 1;                                   // факториал равен 1
    if (++i < number){                               // используем предварительное увеличение i на единицу
        factorial = i * factorialSecond(number);    // заново вызываем функцию факториала
        i--;                                        // декрементируем i
        return factorial;
    }
    i--;
    return number;
}



//Странный вариант if, мне не нравится
int factorialThird(int number){
    return number > 1 ? number * factorialThird(number - 1) : 1;
}



int fibonacci(int numberOf){
    if(numberOf == 0 || numberOf == 1){
        return 1;
    } else {
        return fibonacci(numberOf - 1) + fibonacci(numberOf - 2);
    }
}




void goodStringReverse(char* string, int stringLenght){
    static int i = 0;
    char symbal;
    
    symbal = string[i];
    string[i] = string[stringLenght - 1 - i];                           // замена символов до тех пор пока
    string[stringLenght - 1 - i++] = symbal;

    if (i< (stringLenght / 2)){
        goodStringReverse(string, stringLenght);                        // не достигнута середина строки
    }
    else return;
}



void badStringReverse(char* string, int stringLenght){
    static int i;
    char symbal;
    symbal = string[i++];
    if(symbal){
        badStringReverse(string, stringLenght);
    } else{
        return;
    }
    string[stringLenght - (--i)] = symbal;
    if (i == 1){
        i = 0;
    }
}



void swapArrayElements(int *array, int first, int second){
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}



void hoareArraySorting(int *array, int firstPoint, int secondPoint){
    int i, temp;
    if (firstPoint >= secondPoint){
        return;
    }
    swapArrayElements(array, firstPoint, (firstPoint + secondPoint) / 2);
    temp = firstPoint;
    for (i = firstPoint + 1; i <= secondPoint; i++){
        if (array[i] < array[firstPoint]){
            swapArrayElements(array, ++temp, i);
        }
    }
    swapArrayElements(array, firstPoint, temp);
    hoareArraySorting(array, firstPoint, temp - 1);
    hoareArraySorting(array, temp + 1, secondPoint);
}


void recursReverseLastWord(char *string, int i){
    static int wordFirstSymbalIndex;
    char symbal;
    if (string[i] == ' '){
        wordFirstSymbalIndex = i + 1;                   // запоминаем позицию ' ' перед словом
    }
    if (string[i] != '\0'){                             // если не конец строки
        symbal = string[i++];                           // чтение символа из строки
        recursReverseLastWord(string, i);               // рекурсия
    }
    else {
        return;                                         // строка окончена
    }
    printf("\n i = %d  firstWordSymbalIndex = %d", i, wordFirstSymbalIndex);
    if (string[wordFirstSymbalIndex] != '\0') {
        string[wordFirstSymbalIndex++] = symbal;        //реверс слова
    }
    if (i==1){
        wordFirstSymbalIndex = 0;
    }
}
