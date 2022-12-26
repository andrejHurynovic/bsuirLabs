//
//  main.cpp
//  Labwork 2. MMX
//
//  Created by Andrej Hurynovič on 18.03.21.
//

#include <iostream>
#include <iomanip>
#include "Timer.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    const int matrixHeight = 16;
    const int matrixWidth = 16;
    
    const int numberOfOperations = 100000;
    
    cout << "Test values: matrixHeight = " << matrixHeight << endl
    << "             matrixWidth = " << matrixWidth << endl
    << "             numberOfOperations = " << numberOfOperations << endl;
    
    
    cout << "|    C++    | Assembley |    MMX    |    SSE    |" << endl;
    
    int matrix[matrixHeight][matrixWidth];
    
    int newMatrix[matrixHeight][matrixWidth];
    
    for(int i = 0; i < matrixHeight; i++){
        for(int j = 0; j < matrixWidth; j++){
            matrix[i][j] = rand();
        }
    }
    
    
    
    Timer timer;
    double resultTime;
    
    do {
        
        int32_t temp32a;
        int* pointerTemp32a = (int*)&temp32a;
        int32_t temp32b;
        int* pointerTemp32b = (int*)&temp32b;

        resultTime = 0;

        //C++
        for(int d = 0; d < numberOfOperations; d++){
            for(int i = 0; i < matrixHeight; i++){
                for(int j = 0; j < matrixWidth; j++){
                    timer.reset();

                    *pointerTemp32a = matrix[i][j];
                    temp32b = temp32a;
                    newMatrix[i][j] = *pointerTemp32b;

                    resultTime += (timer.elapsed());
                }
            }

        }

        cout << '|' << fixed << setprecision(9) << resultTime << '|';

        //Assembly

        resultTime = 0;

        for(int d = 0; d < numberOfOperations; d++){
            for(int i = 0; i < matrixHeight; i++){
                for(int j = 0; j < matrixWidth; j++) {
                    *pointerTemp32a = (matrix[i][j]);

                    timer.reset();
                    __asm {
                        mov eax, temp32a
                        mov temp32b, eax
                    }
                    resultTime +=timer.elapsed();
                    newMatrix[i][j] = *pointerTemp32b;
                }
            }

        }

        cout << fixed << setprecision(9) << resultTime << '|';

        //MMX

        resultTime = 0;

        int64_t temp64a;
        int* pointerTemp64a = (int*)&temp64a;
        int64_t temp64b;
        int* pointerTemp64b = (int*)&temp64b;


        for(int d = 0; d < numberOfOperations; d++){
            for(int i = 0; i < matrixHeight; i++) {
                for(int j = 0; j < matrixWidth; j++) {
                    pointerTemp64a[0] = (matrix[i][j]);
                    pointerTemp64a[1] = (matrix[i][j + 1]);

                    timer.reset();
                    __asm {
                        movq mm0, temp64a
                        
                        movq temp64b, mm0
                        EMMS
                    }
                    resultTime +=timer.elapsed();
                    newMatrix[i][j++] = *(pointerTemp64b);
                    newMatrix[i][j] = *((pointerTemp64b) + 1);
                }
            }
        }

        cout << fixed << setprecision(9) << resultTime << '|';
        
        //SSE

        resultTime = 0;
        
        __int128 temp128a;
        int* pointerTemp128a = (int*)&temp128a;
        __int128 temp128b;
        int* pointerTemp128b = (int*)&temp128b;

        
        for(int d = 0; d < numberOfOperations; d++){
            for(int i = 0; i < matrixHeight; i++) {
                for(int j = 0; j < matrixWidth; j++) {
                    pointerTemp128a[0] = (matrix[i][j]);
                    pointerTemp128a[1] = (matrix[i][j + 1]);
                    pointerTemp128a[2] = (matrix[i][j + 2]);
                    pointerTemp128a[3] = (matrix[i][j + 3]);

                    
                    timer.reset();
                    __asm {
                        movups xmm0, temp128a
                        movups temp128b, xmm0
                    }
                    resultTime +=timer.elapsed();
                    newMatrix[i][j++] = *(pointerTemp128b);
                    newMatrix[i][j++] = *((pointerTemp128b) + 1);
                    newMatrix[i][j++] = *((pointerTemp128b) + 2);
                    newMatrix[i][j] = *((pointerTemp128b) + 3);
                }
            }
        }

        cout << fixed << setprecision(9) << resultTime << '|';
        
        cout << endl;
        
//        if(getchar() == 'Q'){
//            break;
//        }
        
    }while(true);
    
    
    return 0;
}
