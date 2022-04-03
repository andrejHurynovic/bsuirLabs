//
//  Circle.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "TwoDismensionShape.h"

class Circle: public TwoDismensionShape{
public:
    Circle(int radius = 0){
        cout << "Circle" << endl;
        this->a = radius;
    };
    
    float getArea() override;
    
    const char * getName() override;
    
    float getVolume() override;
    
    ~Circle(){
        cout << "~Circle" << endl;
    };
};
