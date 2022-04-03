//
//  Square.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "TwoDismensionShape.h"

class Square: public TwoDismensionShape{
public:
    Square(int a = 0){
        cout << "Square" << endl;
        this->a = a;
    };
    
    float getArea() override;
    
    const char * getName() override;
    
    float getVolume() override;
    
    ~Square(){
        cout << "~Square" << endl;
    };
};
