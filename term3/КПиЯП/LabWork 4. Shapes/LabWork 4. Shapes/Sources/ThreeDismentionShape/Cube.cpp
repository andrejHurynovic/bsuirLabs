//
//  Cube.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Cube.h"

    float Cube::getArea(){
        return 6 * a * a;
    }
    
    float Cube::getVolume(){
        return a * a * a;
    }
    
    const char * Cube::getName(){
        return "Cube";
    }
