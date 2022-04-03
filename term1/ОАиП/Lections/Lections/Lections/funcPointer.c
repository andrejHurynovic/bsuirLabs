//
//  funcPointer.c
//  Lections
//
//  Created by Андрэй Гурыновіч on 1/14/20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

#include <stdio.h>
#include <math.h>


double integralFunc(double x){
    return (x*x - 4.);
}



double integralUsingTrapeze(double(*underIntegralFunction)(double), double buttomLimit, double upperLimit, double accuracy, int maximalIteration){
    double y1;
    double y2 = 0;
    double agrument;
    double step = (upperLimit - buttomLimit) / maximalIteration;
    do{
        y1 = y2;
        y2 = 0.5 * ((*underIntegralFunction)(buttomLimit) + (*underIntegralFunction)(upperLimit));
        for (agrument = buttomLimit + step; agrument<upperLimit; agrument += step){
            y2 += (*underIntegralFunction)(agrument);
        }
        y2 *= step;
        step /= 2.0;
    } while (fabs(y1 - y2) > accuracy);
    return y2;
}



double integralUseingRectangle(double(*underIntegralFunction)(double), double buttomLimit, double upperLimit, double accuracy, int maximalIteration){
    double y1;
    double y2 = 0.0;
    double agrument;
    double step = (upperLimit - buttomLimit) / maximalIteration;
    do{
        y1 = y2; y2 = 0.0;
        for (agrument = buttomLimit; agrument < upperLimit; agrument += step)
            y2 += (*underIntegralFunction)(agrument) * step;
        step /= 2;
    } while (fabs(y1 - y2) > accuracy);
    return y2;
}





// использование указателя на функцию на примере
// вычисления корня нелинейного уравнения методом " ПОЛОВИННОГО ДЕЛЕНИЯ "




double halfDivideMethod(double a, double b, double accuracy, double(*function)(double)){
    double functionAtA, functionAtB, functionAtC;
    double c;
    do{
        functionAtA = (*function)(a);               // нахождение значений функции в концах
        functionAtB = (*function)(b);               // выбранного интервала   [a,b]
        c = (a + b) / 2.0;                          // деление отрезка [a,b] пополам
        functionAtC = (*function)(c);               // значение функции в середине отрезка
        if (functionAtA * functionAtC > 0){
            a = c;                                  //  выбор границ [c,b]
        } else {
            if (functionAtB * functionAtC > 0){
                b = c;                              //  выбор границ [a,c]
            } else {
                puts("точный корень");
                return c;
            }
        }
    }while (fabs(a - b) > accuracy);                // пока не достигнута точность  eps
    return c;
}

double function(double x){
    return (x*x - 3.);                              // вычисление значения ф-ции f(x)=x^2-3 в точке х
}



//int main(){
//    double a, b, accuracy;
//    double(*functionForCalculation)(double x);
//
//    puts("введите границы a и b и точность вычисления корня");
//    scanf("%lf%lf%lf", &a, &b, &accuracy);
//    functionForCalculation = function;
//    printf("a= %5.2lf  b=%5.2lf  корень = %6.4lf\n", a, b, halfDivideMethod(a, b, accuracy, functionForCalculation));
//}
//                      // [ нахождение квадратного кореня из 3 ]



void firtsFunction(){
    puts("firtsFunction");
}
void secondFunction(){
    puts("secondFunction");
}
void thirdFunction(){
    puts("thirdFunction");
}



int menu(){
    
    char symbal;;
    do{
        puts("1    firtsFunction");
        puts("2    secondFunction");
        puts("3    thirdFunction");
        puts("0    выход");
        rewind(stdin);
        scanf("%c", &symbal);   // тут бы getch(), но у меня не работает
    } while (symbal < '0' || symbal > '3');
    return symbal - 49;
}

void workWithMenu(){
    void (*functionList[])(void) = {firtsFunction, secondFunction, thirdFunction};
    
    int i = menu();
    while(i != -1){
        functionList[i]();
        i = menu();
    }
}
