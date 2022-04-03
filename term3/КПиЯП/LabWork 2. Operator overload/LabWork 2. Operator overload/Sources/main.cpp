//
//  main.cpp
//  LabWork 1. Class
//
//  Created by Андрэй Гурыновіч on 7.09.20.
//

#include "matrix.hpp"


int main(int argc, const char * argv[]) {
    
    Matrix firstMatrix = NULL;
    Matrix secondMatrix = NULL;
    
    int temp;   //хранение значений для работы меню
    int size;   //хранение размеров матрицы для вызова конструктора
    
    do{
        
        cout << "\n1. Summarize matrixes \n2. Multiply matrixes \n0. Exit\n";
        cin >> temp;
        
        if(!temp){      //выход при temp == 0
            break;
        }
        
        if(temp > 2){   //повтор ввода при temp > 2
            cout << "Incorrect value\n";
            continue;
        }
        
        cout << "Chose matrix size: ";      //ввод размера матрицы
        cin >> size;
        if(size < 1){                       //размер матрицы не может менее единицы
            cout << "the matrix size cannot be less than 1\n";
            continue;
        }
        cout << "Matrix size: " << size << "\n";
        
        cout << "Enter first matrix:\n";
        firstMatrix = Matrix(size);             //в существующую матрицу через конструктор копирования заносится новая матрица с размеров size
        firstMatrix.enterMatrix();              //вввод матрицы
        cout << "The first matrix:\n";
        firstMatrix.showMatrix();               //вывод матрицы
        
        cout << "Enter second matrix:\n";
        secondMatrix = Matrix(size);
        secondMatrix.enterMatrix();
        cout << "The second matrix:\n";
        secondMatrix.showMatrix();
        
        Matrix resultMatrix = NULL;
        
        switch (temp) {                         //switch  для выбора операции
            case 1:
                resultMatrix = firstMatrix + firstMatrix;       //проведение операции суммирования
                break;
            case 2:
                resultMatrix = firstMatrix * secondMatrix;      //проведение операции умножения
                break;
        }
        
        cout << "Result matrix:\n";
        resultMatrix.showMatrix();       //вывод результатов операции
        
    }while(temp);
    
}
