





#include<stdio.h>
#include<stdlib.h>



//char* createAndScanString(){
//    char *string;
//    int stringLenght;
//    do{
//        printf("String lenght: ");
//        rewind(stdin);
//        scanf("%d", &stringLenght);
//    }while (stringLenght < 1);
//    char error = 0;
//    do{
//        if (!(string = (char *)malloc(stringLenght + 1))){
//            error = 1;
//        }
//    }while (error == 1);
//    
//    rewind(stdin);
//    printf("\nEnter string: ");
//    fgets(string, stringLenght + 1, stdin);
//    return string;
//}



//void swapElementsBetweenTwoPoints(char* firstPoint,char* secondPoint){
//    char temp;
//    for (; firstPoint < secondPoint; firstPoint++, secondPoint--){
//        temp = *firstPoint;
//        *firstPoint = *secondPoint;
//        *secondPoint = temp;
//    }
//}



//void swapTwoFirstWords(){
//    char *string = createAndScanString();
//    
//    int i = 0, firstWordFirstIndex, firstWordLastIndex, secondWordFirstIndex, secondWordLastIndex;
//    //пропуск пробелов
//    while(*(string + i) == ' '){
//        i++;
//    }
//    firstWordFirstIndex = i;
//    
//    while (*(string+i) && *(string + i) != ' '){
//        i++;
//    }
//    firstWordLastIndex = i - 1;
//    
//    while (*(string + i) == ' '){
//        i++;
//    }
//    secondWordFirstIndex = i;
//    
//    while (*(string + i) && *(string + i) != ' '){
//        i++;
//    }
//    secondWordLastIndex = i - 1;
//    
//    //переворачивает все элементы между точками
//    swapElementsBetweenTwoPoints(&string[firstWordFirstIndex], &string[secondWordLastIndex]);
//    //переворачиваем второе слово
//    swapElementsBetweenTwoPoints(string + secondWordLastIndex - (firstWordLastIndex - firstWordFirstIndex), string + secondWordLastIndex);
//    //переворачиваем первое слово
//    swapElementsBetweenTwoPoints(string + firstWordFirstIndex, string + firstWordFirstIndex+(secondWordLastIndex-secondWordFirstIndex));
//    printf("\nResult: %s", string);
//    free(string);
//}
//
//
//
////удаление длиннейшего слова (плохая реализациия, лучше через wordLenght)
//void removeLargestWordFromString(){
//    char *string = createAndScanString();
//    
//    int wordFirstIndex = 0, wordLastIndex = 0, wordFirstIndexTemp, wordLastIndexTemp, i = 0;
//    while(*(string + i)){
//        while(*(string + i) == ' '){
//            i++;
//        }
//        wordFirstIndexTemp = i;
//        while(*(string + i) != ' ' && *(string + i)) {
//            i++;
//        }
//        wordLastIndexTemp = i - 1;
//        if(wordLastIndexTemp - wordFirstIndexTemp > wordLastIndex - wordFirstIndex){
//            wordFirstIndex = wordFirstIndexTemp;
//            wordLastIndex =  wordLastIndexTemp;
//        }
//        
//    }
//    
//    for (i = wordFirstIndex; i <= wordLastIndex; printf("%c", *(string + i++)));
//    for (; (*(string + wordFirstIndex) = *(string + wordLastIndex + 1)); wordFirstIndex++, wordLastIndex++){};
//    printf("\nResult: %s", string);
//}



//int stringToInt(char *string){
//    int i = 0, number, polarity;
//    while (string[i] == ' '){
//        i++;
//    }
//    if (!string[i]){
//        printf("error, empty string");
//    }
//    polarity = (string[i] == '-') ? -1 : 1;         // запоминаем знак числа
//    if (string[i] == '+' || string[i] == '-'){
//        i++;
//    } // пропуск знака
//    
//    for (number = 0; string[i] >= '0' && string[i] <= '9'; i++){
//        number = 10 * number + (string[i] - '0');
//    }  // выбор цифр числа из строки
//    return polarity * number;                       // возврат числа со знаком
//}



char* intToString(int number){
    int stringLenght = 0;
    int tempNumber = number;
    char *string;
    
    do { //находим stringLenght
        tempNumber /= 10 * (stringLenght + 1);
        stringLenght++;
    } while (tempNumber > 1);
    if(number < 0){
        stringLenght++;
    }
    
    char error = 0;
    do{
        if (!(string = (char *)malloc(stringLenght + 1))){
            error = 1;
        }
    }while (error == 1);
    
    int polarity, i = 0;
    polarity = number;
    if (polarity < 0)                               // сохраняем знак
        number *= -1;                               // n- положительное число
    do{                                             // цифры заносим в строку в обратном порядке
        string[i++] = number % 10 + '0';            // выделяется последний справа разряд
    } while ((number /= 10) > 0);                   // удаляется цифра из числа
    
    if (polarity < 0) string[i++] = '-';
    string[i] = '\0';                               // заносится признак конца строки
    for (number = 0; number < i / 2; number++){     // реверс (переворот) полученной строки
        string[number] += string[i - 1 - number];
        string[i - 1 - number] = string[number] - string[i - 1 - number];
        string[number] -= string[i - 1 - number];
    }
    string[stringLenght] = '\0';
    return string;
}



int stringsComparison(char *firstString, char *secondString){
    while (*firstString && *secondString && !(*firstString - *secondString)){ // пока не достигнут конец одной из строк
                                            // и пока символы в строках совпадают
        firstString++;                      // выбор к анализу следующей пары символов
        secondString++;
    }
    return *firstString-*secondString;      //выдсёт первый несовпадающий символ
}



int getStringLenght(char** string){
    int lenght = 0;
    for(;string[lenght] != '\0'; lenght++){}
    return lenght;
}



//записывает строку и "\0" в конце
int getString(char *string, int maximalLenght){
    char symbal;
    int i = 0;
    printf("\nВводите вторую строку  ");
    // символы заносятся в буфер и после нажатия Enter k-1 символ
    // из буфера переносятся в строку
    while (--maximalLenght > 0 && (symbal = getchar()) != EOF && symbal != '\n')
        string[i++] = symbal;   // ввод строки до заданного кол-ва символов или пока
    // не нажата клавиша Enter или Ctrl + Z
    string[i] = '\0';
    return i;    // возврат длинны строки
}








char* getString2(char *string){
    int i = 0;
    while ((string[i++] = (char)getchar()) != '\n');
    string[--i] = '\0';
    return string;
}



void addStringToStringAtPoint(char* firstString, int firstStringLenght, char* secondString, int secondStringLenght, int interventionPoint){
    int resultLenght = firstStringLenght + secondStringLenght;
    firstString = realloc(firstString, (sizeof(char) * resultLenght) + 1);
    for(int i = resultLenght; i > interventionPoint + secondStringLenght - 1; i--){
        firstString[i] = firstString[i - secondStringLenght];
    }
    for(int i = interventionPoint; i < secondStringLenght + interventionPoint; i++){
        firstString[i] = secondString[i - interventionPoint];
    }
    firstString[resultLenght + 1] = '\0';
    puts(firstString);
}
