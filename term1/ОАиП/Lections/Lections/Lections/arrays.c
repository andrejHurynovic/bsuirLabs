//
//  arrays.c
//  Arrays
//
//  Created by Андрэй Гурыновіч on 11/3/19.
//  Copyright © 2019 Андрэй Гурыновіч. All rights reserved.
//


#include<stdio.h>
#include <stdlib.h>


void ScanIntArrayWithLenght(int array[], int lenght){
    int i = 0;
    while (i < lenght) {
        rewind(stdin);
        printf("array[%d] = ", i);
        if (scanf("%d", &array[i])){
            i++;
        }
    }
}

void ScanIntArrayWithMonotony(int type, int array[], int lenght){
    if (type == 0) {
        printf("Increase\n");
    } else {
        printf("Decrease\n");
    }
    
    int i = 0;
    while (i < lenght) {
        rewind(stdin);
        printf("array[%d] = ", i);
        if ((scanf("%d", &array[i]) && ((type == 0 && array[i] >= array[i-1]) || (type == 1 && array[i] <= array[i-1]))) || i == 0){
            i++;
        }
    }
}

void PrintIntArray(int array[], int lenght){
    for (int i = 0; i < lenght; i++)
        printf("%4d", array[i]);
}



void ElemetReverse(){
    const int lenght = 4;
    int array[lenght];
    ScanIntArrayWithLenght(array, lenght);
    
    printf("Before: ");
    PrintIntArray(array, lenght);
    
    int minNumberIndex = 0, maxNumberIndex = 0;
    for (int i = 1; i < lenght; i++)
        if (array[i] < array[minNumberIndex]){
            minNumberIndex = i;
        } else if (array[i] > array[maxNumberIndex]){
            maxNumberIndex = i;
        }
    
    printf("\nmin = %d  max = %d\n", array[minNumberIndex],array[maxNumberIndex]);
    //Для того, чтобы maxNumberIndex не был больше minNumberIndex
    if (minNumberIndex > maxNumberIndex){
        int i = minNumberIndex; minNumberIndex = maxNumberIndex; maxNumberIndex = i;
    }
    
    for (; minNumberIndex < maxNumberIndex; minNumberIndex++, maxNumberIndex--){
        //Какая-то охуенная сиситема, в жизни бы не догадался, нужно запомнить
        array[minNumberIndex] += array[maxNumberIndex];
        array[maxNumberIndex] = array[minNumberIndex] - array[maxNumberIndex];
        array[minNumberIndex] -= array[maxNumberIndex];
    }
    PrintIntArray(array, lenght);
}


void ArraysUnite(){
    const int firstLenght = 2;
    const int secondLenght = 4;
    const int monotonyType = 0;
    
    int firstArray[firstLenght], secondArray[secondLenght], resultArray[firstLenght+secondLenght];
    ScanIntArrayWithMonotony(monotonyType,firstArray,firstLenght);
    ScanIntArrayWithMonotony(monotonyType, secondArray, secondLenght);
    PrintIntArray(firstArray, firstLenght);
    printf("\n");
    PrintIntArray(secondArray, secondLenght);
    printf("\n");
    
    int i1 = 0, i2 = 0, i3 = 0;
    do {
        while (firstArray[i1] <= secondArray[i2] && i1 < firstLenght){
            resultArray[i3++] = firstArray[i1++];
            if (i1 >= firstLenght) break;
        }
        while (firstArray[i1] > secondArray[i2] && i2 < secondLenght){
            resultArray[i3++] = secondArray[i2++];
        }
    } while (i1<firstLenght && i2<secondLenght);        // до тех пор, пока однин из массивов не закончится
    
    while (i1<firstLenght) resultArray[i3++] = firstArray[i1++];
    while (i2<secondLenght) resultArray[i3++] = secondArray[i2++]; //добавляет оставшивеся значения
    
    PrintIntArray(resultArray, firstLenght+secondLenght);
}



void SelectionArraySorting(int lenght, int array[]){    // отбор
    int j, m, temp;
    for (int i = 0; i < lenght - 1; ++i){
        m = i;                                          // индекс элемента для упорядочивания
        for (j = i + 1; j < lenght; ++j){               // перебор последующих эл-тов справа от i-го
            if (array[j] < array[m]){                   // найден меньший
                m = j;                                  // запоминаем его индекс
            }
        }
        
        temp = array[m];
        array[m] = array[i];                            // замена выбранного и меньшего
        array[i] = temp;
    }
}



void InsertArraySorting(int lenght, int array[]){ //вставка
    int temp;
    for(int i = 1; i < lenght; i++){
        for(int j = i; j > 0 && array[j - 1] > array[j]; j--){
            temp = array[j - 1];
            array[j - 1] = array[j];
            array[j] = temp;
        }
    }
}



void BubbleArraySorting(int lenght, int array[]){       //пузырёк
    int temp;
    int haveOperation = 1;
    for(int i = 1; i < lenght && haveOperation; i++){
        haveOperation = 0;
        for(int j = 0; j + i < lenght; j++){
            if(array[j] > array[j + 1]){
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
                haveOperation = 1;
            }
        }
    }
}



void ShakerArraySorting(int lenght, int *array){
    int leftBorder = 0;
    int rightBorder = lenght - 1;
    int temp;
    int i;
    int haveOperation;
    do{
        haveOperation = 0;
        for(i = leftBorder; i < rightBorder; i++){
            if(array[i] > array[i + 1]){
                temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
                haveOperation = 1;
            }
        }
        if(!haveOperation){
            break;
        }
        
        haveOperation = 0;
        for(i = --rightBorder - 1; i >= leftBorder; i--){
            if(array[i] > array[i + 1]){
                temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
                haveOperation = 1;
            }
        }
        if(!haveOperation){
            break;
        }
        
        leftBorder++;
    }while(leftBorder < rightBorder);
}


void ArraySortingMethods(){
    const int lenght = 5;
    int array[lenght];
    ScanIntArrayWithLenght(array, lenght);
    
    fflush(stdin);
    switch (getchar()){
        case '1': SelectionArraySorting(lenght, array); break;
        case '2': InsertArraySorting(lenght, array); break;
        case '3': BubbleArraySorting(lenght, array); break;
        case '4': ShakerArraySorting(lenght,array); break;
        default: printf("Error");
    }
    
    PrintIntArray(array, lenght);
}



void AddNumberToArrayWithMonotony (){
    int lenght;
    do{
        printf("Array length: ");
        rewind(stdin);
        scanf("%d", &lenght);
    }while (lenght <= 0);
    
    int *array = (int *)malloc(lenght * sizeof(int));
    
    ScanIntArrayWithLenght(array, lenght);
    PrintIntArray(array, lenght);
    
    int number;
    
    do{
        printf("\nEnter number: ");
        rewind(stdin);
    }while (!scanf("%d", &number));
    
    int interventionPoint = 0;
    while(interventionPoint < lenght && *(array + interventionPoint) < number){
        interventionPoint++;                                        // поиск точки интервенции
    }
    array = (int *)realloc(array, sizeof(int) * (lenght + 1));      // увеличение выделенной памяти на одну ячейку
    if (interventionPoint == lenght){
        *(array + interventionPoint) = number;                      // если введённое число больше всех остальных добавляем его в конец
    } else {
        int j = lenght;
        while (j > interventionPoint){                              // сдвиг всех элеметнов после точки интервенции вправо
            *(array + (j--)) = *(array + j - 1);
        }
        *(array + interventionPoint) = number;                      // запись числа в массив
    }
    lenght++;
    PrintIntArray(array, lenght);
    free(array);
}



void removeElementsInInterval(){
    int lenght = 10;
    int* array = (int*)malloc(sizeof(int) * lenght);
    ScanIntArrayWithLenght(array, lenght);
    
    int intervalFirst = 7;
    int intervalSecond = 8;
    int range = intervalSecond - intervalFirst + 1;
    
    PrintIntArray(array, lenght);
    printf("\n");
    
    for(int i = intervalFirst; i <= intervalSecond; i++){
        if(i + range > lenght - 1){
            break;
        }
        array[i] = array[i + range];
    }
    
    lenght -= range;
    array = (int*)realloc(array, lenght * sizeof(int));
    PrintIntArray(array, lenght);
}



