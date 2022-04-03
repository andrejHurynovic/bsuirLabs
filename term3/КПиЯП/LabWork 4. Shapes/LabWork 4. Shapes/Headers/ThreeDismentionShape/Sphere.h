//
//  Sphere.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "ThreeDismensionShape.h"

class Sphere: public ThreeDismensionShape{
public:
    Sphere(int radius = 0){
        cout << "Sphere" << endl;
        this->a = radius;
    }
    
    float getArea() override;
    
    float getVolume() override;
    
    const char * getName() override;
        
    ~Sphere(){
        cout << "~Sphere" << endl;
    };
};
