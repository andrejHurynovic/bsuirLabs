////
////  tickets.c
////  Lections
////
////  Created by Андрэй Гурыновіч on 1/15/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//
//
//
//int** createMatrix(int rows, int columns){
//    
//    int** matrix = (int**)malloc(sizeof(int*) * rows);
//    
//    for(int row = 0; row < rows; row++){
//        matrix[row] = (int*)malloc(sizeof(int) * columns);
//    }
//    return matrix;
//}
//void scanMatrix(int **matrix, int rows, int columns){
//    for(int row = 0; row < rows; row++){
//        for(int column = 0; column < columns; column++){
//            do{
//                rewind(stdin);
//                printf("matrix[%d][%d] = ", row, column);
//            }while(!scanf("%d", &matrix[row][column]));
//        }
//    }
//}
//void printMatrix(int **matrix, int rows, int columns){
//    for(int row = 0; row < rows; row++){
//        for(int column = 0; column < columns; column++){
//            printf("%4d", matrix[row][column]);
//        }
//        printf("\n");
//    }
//}
//
// char* createAndScanString(){
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
//
//
//
//
//
//
//
//
//
////4.1 Фибoначи рекурсией
//int funcFibonacci(int number){
//    if(number == 1 || number == 2){
//        return 1;
//    } else {
//        return funcFibonacci(number - 1) + funcFibonacci(number - 2);
//    }
//}
//
//
//
////4.2 Реверс первого и последнего слова в строке
//void reverseString(char* string, int firstPoint, int secondPoint){
//    char symbal;
//    for(; firstPoint < secondPoint; firstPoint++, secondPoint--){
//        symbal = string[firstPoint];
//        string[firstPoint] = string[secondPoint];
//        string[secondPoint] = symbal;
//    }
//}
//
//
//void lastAndFirstWordReverse(char* string){
//    int i = 0;
//    int temp;
//    while(string[i] == ' '){
//        i++;
//    }
//    temp = i;
//    while(string[i] != ' '){
//        i++;
//    }
//    reverseString(string, temp, i - 1);
//    while(string[i] != '\0'){
//        i++;
//    }
//    temp = i - 1;
//    while(string[i - 1] != ' '){
//        i--;
//    }
//    reverseString(string, i, temp);
//}
//
//
//
////6.1 Рекурсивно транспонировать матрицу относительно побочной диагонали(не используя новую матрицу)
////при запуске функции row и column оставлять 0
//void swapMatrixElement(int** matrix, int row, int column, int size){
//    if(row == size - 1){
//        return;
//    }
//    if((row + column == size - 1)){
//        swapMatrixElement(matrix, ++row, 0, size);
//        return;
//    }
//    int temp = matrix[row][column];
//    matrix[row][column] = matrix[size - 1 - column][size - 1 - row];
//    matrix[size - 1 - column][size - 1 - row] = temp;
//    swapMatrixElement(matrix, row, ++column, size);
//}
//
//
//
////6.2 Рекурсивно удалить предпоследнее слово в строке(не используя новую строку)
//void recurseRemoveWord(char* string, int firstPoint, int secondPoint){
//    if(string[secondPoint] == '\0'){
//        string[firstPoint] = '\0';
//    }else{
//        string[firstPoint] = string[secondPoint];
//        return recurseRemoveWord(string, ++firstPoint, ++secondPoint);
//    }
//    
//}
//void removePreLastWordFromString(){
//    char* string = createAndScanString();
//    int secondPoint = 0;
//    while(string[secondPoint] != '\0'){
//        secondPoint++;
//    }
//    secondPoint--;
//    while(string[secondPoint] == ' '){
//        secondPoint--;
//    }
//    while(string[secondPoint] != ' '){
//        secondPoint--;
//    }
//    secondPoint--;
//    int firstPoint = secondPoint;
//    while(string[firstPoint] != ' ' && firstPoint != 0){
//        firstPoint--;
//    }
//    firstPoint++;
//    recurseRemoveWord(string, firstPoint, secondPoint + 1 );
//}
//
//
//
////10.1 Создать функцию перевода из 10-чной в любую, в диапазоне от 2 до 16(вводится пользователем), не используем рекурсий.
//void numerationSystemChange(){
//    
//    char string[20];
//    
//    double number;
//    do {
//        rewind(stdin);
//        printf("Enter number");
//    } while (!scanf("%lf", &number));
//    
//    char polaryty = ' ';
//    if(number < 0){
//        polaryty = '-';
//        number *= -1;
//    }
//    
//    int newNumeralSystem;
//    do{
//        rewind(stdin);
//        printf("Enter new numeral system: ");
//    }while (!scanf("%d", &newNumeralSystem) || newNumeralSystem <= 0 || newNumeralSystem > 33);
//    
//    int accuracyForFractionalPart;
//    do {
//        rewind(stdin);
//        printf("Accuracy for fractional part: ");
//    } while (!scanf("%d", &accuracyForFractionalPart) || accuracyForFractionalPart < 0);
//    
//    int integerPart = number;                               //выделение целой части
//    double fractionalPart = number - integerPart;           //выделение дробной части числа
//    
//    int i = 0;
//    int firstPoint = 10;
//    int secondPoint = firstPoint + 1;
//    while (integerPart >= newNumeralSystem){                //перевод целой части этого числа
//        i = integerPart % newNumeralSystem;
//        integerPart /= newNumeralSystem;
//        if(i > 9){
//            string[firstPoint--] = i - 10 + 'A';
//        } else {
//            string[firstPoint--] = i + '0';
//        }
//    }                                                       //числа в новой системе счисления
//    if(integerPart > 9){
//        string[firstPoint--] = integerPart - 10 + 'A';
//    }else{
//        string[firstPoint--] = integerPart + '0';
//    }
//    if(polaryty == '-'){
//        string[firstPoint] = polaryty;
//    }
//    string[secondPoint++] = '.';
//    
//    while (fractionalPart != 0 && secondPoint - 11 <= accuracyForFractionalPart){
//        fractionalPart *= newNumeralSystem;
//        i = fractionalPart;
//        if(i > 9){
//            string[secondPoint++] = i - 10 + 'A';
//        }else{
//            string[secondPoint++] = i + '0';
//        }
//        fractionalPart -= i; //отбрасываем целую часть
//    }
//    printf("Result: ");
//    for (i = firstPoint; i < secondPoint; i++)
//        printf("%c", string[i]);
//}
//
//
////2.2 В функции перемножить две матрицы циклом do...while
//
////11.1 Разработать функцию которая отдельно считает инты и флоты используя макросы
//.
//
//#include <stdarg.h>
//enum data{Int,Float=2} tp;
//
//void fun(int k, int l, data tp,...)    // k-число групп
//{
//  int si=0;
//  float sf=0;
//  va_list p;           // p - безтиповой указатель
//  va_start(p,tp);
//  while(k--)
//  { switch(tp)
//    { case 2: while(l--) // пока не считаны все переменные группы
//       sf+=va_arg(p,double);    // сумма double (float)
//       break;
//      case Int : while(l--)   // пока не считаны все переменные группы
//       si+=va_arg(p,int);       // сумма int
//    }
//    l=va_arg(p,int);          // считывается число элементов в группе (int)
//    tp=va_arg(p,enum data);   // считывается признак типа элементов группы
//  }
//  va_end(p);
//  printf("\n  si= %d   sf= %lf",si,sf);
//}
//
////int main()
////{
////  fun(3,2,Int,1,2,3,Float,1.2,.8,2.5,4,Int,2,3,4,5);
////  printf("\n");
////  return 0;
////}
//
//
//
////17.1 Не используя массивов ввести группу длинных чисел и вывести их в обратном порядке с их порядковыми номерами.
//
////17.2 Функция сложения int и float;
//
////33.2 Через командную строку В Мейн передать строки(каждая строка-номер года). Найти сумму високосных лет(кратных 4) в функции(строки передавать по одному). Вывести в мейн.
//
////37.2 Разработать рекурсивную функцию реализующую проверку во введёной строке правильность порядка [ ](каждой [ соответствует ])([ ] [ [ ] ] - верно,[ ] ] [ ] [- неверно )
////Дополнительные строки не использовать
//
//
//void func(char*, int, int);
////
////int main() {
////    char* line = (char*)calloc(256, sizeof(char));
////    fgets(line, 255, stdin);
////    func(line, 0, 0);
////    free(line);
////}
//
//int len(char* line) {
//    int i = 0;
//    while (line[i]) i++;
//    return i;
//}
//
//void func(char* line, int c1, int i) {
//    if (line[i]) {
//        if (line[i] == ')') {
//            c1 = 100;
//        }
//        if (line[i] == '(') {
//            c1++;
//            for (int j = 0; j < len(line); j++) {   
//                if (line[j] == ')') {
//                    c1--;
//                    line[j] = '0';
//                    break;
//                }
//            }
//        }
//        i++;
//        func(line, c1, i);
//    }
//    else {
//        if (c1 == 0) puts("Correct");
//        else puts("Incorrect");
//    }
//}
//
//int main(){
//    const arrayLenght = 10;
//    int array[arrayLenght];
//    for(int step = arrayLenght/2; step > 0; step /= 2){
//        for(int i = step; i < arrayLenght; i++){
//            int j, temp;
//            temp = array[i];
//            for(j = i; j >= step; j -= step){
//                if(array[j] < array[j - step]){
//                    
//                }
//            }
//        }
//    }
//}
//
//
//


int main(){
    char str[20];
    

    int check;
    int temp;
    if (check <= 3) {
        for (int i = 0; i < size(str); ++i) {
            if (str[i] == ',') {
                temp = i;
                while (str[temp + 1] != '\0') {
                    str[temp] = str[temp + 1];
                    temp++;
                    check++;
                }
            }
        }
    }
}
