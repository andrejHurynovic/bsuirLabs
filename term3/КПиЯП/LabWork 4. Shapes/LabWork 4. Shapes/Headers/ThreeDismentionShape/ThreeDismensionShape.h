//
//  ThreeDismentionShape.h
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef ThreeDismentionShape_h
#define ThreeDismentionShape_h

#include "Shape.h"

class ThreeDismensionShape: public Shape{
protected:
    int a;
public:
    ThreeDismensionShape(){
        cout << "ThreeDismensionShape" << endl;
};
            
    ~ThreeDismensionShape(){
        cout << "~ThreeDismensionShape" << endl;
    };
};

#endif /* ThreeDismentionShape_h */

