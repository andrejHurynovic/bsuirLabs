//
//  Rectangle.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Rectangle.h"

float Rectangle::getArea(){
    return a * b;
}

const char * Rectangle::getName(){
    return "Rectangle";
}

float Rectangle::getVolume(){
    return 0;
}

