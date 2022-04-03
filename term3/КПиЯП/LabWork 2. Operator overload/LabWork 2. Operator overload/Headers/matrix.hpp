//
//  matrix.hpp
//  LabWork 1. Class
//
//  Created by Андрэй Гурыновіч on 5.09.20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>
#include <iomanip>

using namespace std;                                    //использование пространства имен std

class Matrix{                                           //объявление класса Matrix
    
private:                                                //объявление приватных(недоступных за пределами класса переменных)
    int** matrix;                                       //указатель для матрицы
    int size;                                           //так как матрица является квадратным двумерным массивом, для хранения её размера выделяется одна целочисленная переменная
    
public:
    Matrix(int size);
    Matrix& operator= (const Matrix&);
    void enterMatrix();
    void showMatrix();
    Matrix operator+ (const Matrix&);
    Matrix operator* (const Matrix&);
    ~Matrix();
};

#endif /* matrix_hpp */
