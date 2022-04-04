//
//  main.cpp
//  АВП, ЛР № 1
//
//  Created by Andrej Hurynovič on 1.04.22.
//

//Вариант: float 2x1

#include <iostream>
#include <array>
#include <random>
#include <immintrin.h>

#include "logger.h"

using namespace::std;

const int innerRowSize = 2;
const int finalMatrixSize = 512;

float firstMatrix[finalMatrixSize][finalMatrixSize][innerRowSize];
float secondMatrix[finalMatrixSize][finalMatrixSize][innerRowSize];
float resultMatrix[finalMatrixSize][finalMatrixSize][innerRowSize];
float previousMatrix[finalMatrixSize][finalMatrixSize][innerRowSize];



void randomizeFirstAndSecondMatrix() {
    random_device randomDevice;
    mt19937 e{randomDevice()};
    uniform_real_distribution<> dist{1, 500};
    
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            for(int k = 0; k < innerRowSize; k++) {
                firstMatrix[i][j][k] = dist(randomDevice);
            }
        }
    }
    
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            for(int k = 0; k < innerRowSize; k++) {
                secondMatrix[i][j][k] = dist(randomDevice);
            }
        }
    }
}

void cleanResult() {
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            for(int k = 0; k < innerRowSize; k++) {
                resultMatrix[i][j][k] = 0;
            }
        }
    }
}

void copyMatrix() {
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            previousMatrix[i][j][0] = resultMatrix[i][j][0];
            previousMatrix[i][j][1] = resultMatrix[i][j][1];
        }
    }
}

bool compareMatrix() {
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            if(previousMatrix[i][j][0] != resultMatrix[i][j][0] || previousMatrix[i][j][1] != resultMatrix[i][j][1]) {
                cout << "Matrixes are not equal!" << endl;
                return false;
            }
        }
    }
    return true;
}



void withoutAutomaticVectorization() {
    LOG_DURATION("Without automatic vectorization:  ");
    #pragma clang loop vectorize(disable)
    for (int i = 0; i < finalMatrixSize; i++) {
        #pragma clang loop vectorize(disable)
        for (int j = 0; j < finalMatrixSize; j++) {
            float constantA = firstMatrix[i][j][0];
            float constantB = firstMatrix[i][j][1];
            #pragma clang loop vectorize(disable)
            for (int k = 0; k < finalMatrixSize; k++) {
                resultMatrix[i][k][0] += constantA * secondMatrix[j][k][0];
                resultMatrix[i][k][1] += constantB * secondMatrix[j][k][1];
            }
        }
    }
}

void withAutomaticVectorization() {
    LOG_DURATION("With automatic vectorization:     ");
    for (int i = 0; i < finalMatrixSize; i++) {
        for (int j = 0; j < finalMatrixSize; j++) {
            float constantA = firstMatrix[i][j][0];
            float constantB = firstMatrix[i][j][1];
            #pragma clang loop vectorize(enable) interleave(enable)
            for (int k = 0; k < finalMatrixSize; k++) {
                resultMatrix[i][k][0] += constantA * secondMatrix[j][k][0];
                resultMatrix[i][k][1] += constantB * secondMatrix[j][k][1];
            }
        }
    }
}

void withManualVectorization() {
    LOG_DURATION("Without automatic vectorization:  ");
    #pragma clang loop vectorize(disable)
    for (int i = 0; i < finalMatrixSize; i++) {
        #pragma clang loop vectorize(disable)
        for (int j = 0; j < finalMatrixSize; j++) {
            __m256 constant = _mm256_set_ps(firstMatrix[i][j][1],
                                            firstMatrix[i][j][0],
                                            firstMatrix[i][j][1],
                                            firstMatrix[i][j][0],
                                            firstMatrix[i][j][1],
                                            firstMatrix[i][j][0],
                                            firstMatrix[i][j][1],
                                            firstMatrix[i][j][0]);
            #pragma clang loop vectorize(disable)
            for (int k = 0; k < finalMatrixSize; k += 4) {
                __m256 secondMatrixVector = _mm256_loadu_ps(&secondMatrix[j][k][0]);
                __m256 multiplyResult = _mm256_mul_ps(constant, secondMatrixVector);
                __m256 resultMatrixVector = _mm256_loadu_ps(&resultMatrix[i][k][0]);
                __m256 sumOfResultVectorAndMultiplyResult = _mm256_add_ps(resultMatrixVector, multiplyResult);
                _mm256_storeu_ps(&resultMatrix[i][k][0], sumOfResultVectorAndMultiplyResult);
            }
        }
    }
}



int main(int argc, const char * argv[]) {
    
    randomizeFirstAndSecondMatrix();
    
    for (int i = 0; i < 4; i++) {
        withoutAutomaticVectorization();
        
        copyMatrix();
        compareMatrix();
        cleanResult();
        
        withAutomaticVectorization();
        
        copyMatrix();
        compareMatrix();
        cleanResult();
        
        withManualVectorization();
        
        copyMatrix();
        compareMatrix();
        cleanResult();
        
        cout << endl;
    }
    return 0;
}
