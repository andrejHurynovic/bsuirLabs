//
//  Shape.h
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef Shape_h
#define Shape_h

#include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES

using namespace std;

class Shape{
public:
    Shape(){
        cout << "Shape" << endl;
    };
    
    virtual const char* getName() = 0;
    virtual float getArea() = 0;
    virtual float getVolume() = 0;

    virtual ~Shape(){
        cout << "~Shape" << endl;
    };
};

#endif /* Shape_h */
