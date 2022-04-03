//
//  Parallelepiped.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Parallelepiped.h"

    float Parallelepiped::getArea(){
        return 2 * (a * b + b * c + a * c);
    }
    
    float Parallelepiped::getVolume(){
        return a * b * c;
    }
    
    const char * Parallelepiped::getName(){
        return "Parallelepiped";
    }
