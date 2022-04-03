//
//  Sphere.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Sphere.h"

    float Sphere::getArea(){
        return 4 * M_PI * a * a;
    }
    
    float Sphere::getVolume(){
        return 4 / 3 * M_PI * a * a * a;
    }
    
    const char * Sphere::getName(){
        return "Sphere";
    }
