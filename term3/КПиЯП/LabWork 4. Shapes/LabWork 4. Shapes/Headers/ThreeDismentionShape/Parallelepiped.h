//
//  Parallelepiped.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "ThreeDismensionShape.h"

class Parallelepiped: public ThreeDismensionShape{
protected:
    int b, c;
public:
    Parallelepiped(int a = 0, int b = 0, int c = 0){
        cout << "Parallelepiped" << endl;
        this->a = a;
        this->b = b;
        this->c = c;
    }
    
    float getArea() override;
    
    float getVolume() override;
    
    const char * getName() override;
    
    ~Parallelepiped(){
        cout << "~Parallelepiped" << endl;
    };
};
