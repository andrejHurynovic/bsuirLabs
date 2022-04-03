//
//  Cube.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "ThreeDismensionShape.h"

class Cube: public ThreeDismensionShape{
public:
    Cube(int a = 0){
        cout << "Cube" << endl;
        this->a = a;
    }
    
    float getArea() override;
    
    float getVolume() override;
    
    const char * getName() override;
    
//    dynamic type id
    
    ~Cube(){
        cout << "~Cube" << endl;
    };
};
