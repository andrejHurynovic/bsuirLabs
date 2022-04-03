//
//  matrix.cpp
//  LabWork 1. Class
//
//  Created by Андрэй Гурыновіч on 7.09.20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

#include "matrix.hpp"

Matrix::Matrix(int size){                                   //конструктор класса
    this->size = size;
    
    matrix = new int*[size];                                //выделение памяти для матрицы через функцию new
    for (int i = 0; i < size; i++){
        matrix[i] = new int[size];
    }
}

Matrix& Matrix:: operator = (const Matrix &other){               //перегрузка оператора присваивания класса
    
    if(&other != this){
    
    for(int i = 0; i < size; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    
    this->size = other.size;
    this->matrix = new int*[size];
    for(int i = 0; i < size; i++){
        this->matrix[i] = new int[size];
    }
    
    for(int h = 0; h < size; h++){
        for(int w = 0; w < size; w++){
            this->matrix[h][w] = other.matrix[h][w];
        }
    }
    
    }
    return *this;
}

void Matrix::enterMatrix(){                                 //ввод матрицы через cin
    for(int h = 0; h < size; h++){
        for (int w = 0; w < size; w++){
//            cout << "matrix[" << h << "][" << w << "] = ";
            cin >> matrix[h][w] ;
        }
    }
}

void Matrix::showMatrix(){                                  //вывод матрицы в консоль через cout
    for (int h = 0; h < size; h++){
        for (int w = 0; w < size; w++) {
            cout << setw(4) << matrix[h][w] << " ";
        }
        cout << endl;
    }
}

void Matrix::summation(Matrix &additionalMatrix){             //суммирование матрицы, функция принимает адрес второй матрицы и добавляет её к первой через функцию getValueFor, таким образом результатом вычислений явлеяется объект хранящийся в переменной firstMatrix
    for (int h = 0; h < size; h++){
        for (int w = 0; w < size; w++) {
            matrix[h][w] += additionalMatrix.matrix[h][w];
        }
    }
}

void Matrix::multiplication(Matrix &additionalMatrix){        //аналогично, но с умножением
    for (int h = 0; h < size; h++){
        for (int w = 0; w < size; w++) {
            matrix[h][w] *= additionalMatrix.matrix[h][w];
        }
    }
}


Matrix::~Matrix(){                                          //деструктор класс, освобождает память задействованную для  хранения матрицы
    for(int i = 0; i < size; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
}
