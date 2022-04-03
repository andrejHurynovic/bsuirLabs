//
//  Rectangle.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "TwoDismensionShape.h"

class Rectangle: public TwoDismensionShape{
protected:
    int b;
public:
    Rectangle(int a = 0, int b = 0){
        cout << "Rectangle" << endl;
        this->a = a;
        this->b = b;
    };
    
    float getArea() override;
    
    const char * getName() override;
    
    float getVolume() override;

    ~Rectangle(){
        cout << "~Rectangle" << endl;
};
};
