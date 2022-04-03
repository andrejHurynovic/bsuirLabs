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


void cleanResult() {
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            for(int k = 0; k < innerRowSize; k++) {
                resultMatrix[i][j][k] = 0;
            }
        }
    }
}

void hashMatrix() {
    hash<string> stringHash;
    
//    stringHash();
}

int main(int argc, const char * argv[]) {
    std::random_device rd;
    std::mt19937 e{rd()};
    std::uniform_real_distribution<> dist{1, 500};
    
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            for(int k = 0; k < innerRowSize; k++) {
                firstMatrix[i][j][k] = dist(rd);
            }
        }
    }
    
    for(int i = 0; i < finalMatrixSize; i++) {
        for(int j = 0; j < finalMatrixSize; j++) {
            for(int k = 0; k < innerRowSize; k++) {
                secondMatrix[i][j][k] = dist(rd);
            }
        }
    }
    
    for (int i = 0; i < 6; i++) {
        withoutAutomaticVectorization();
        cleanResult();
        withAutomaticVectorization();
        cleanResult();
        withManualVectorization();
        cleanResult();
        cout << endl;
    }
    
    return 0;
}
