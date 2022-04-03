//
//  Circle.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Circle.h"

    float Circle::getArea(){
        return a * a * M_PI;
    }
    
    const char * Circle::getName(){
        return "Circle";
    }

float Circle::getVolume(){
    return 0;
}
