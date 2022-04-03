//
//  TwoDismensionShape.h
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef TwoDismensionShape_h
#define TwoDismensionShape_h

#include "Shape.h"

class TwoDismensionShape: public Shape{
protected:
    int a;
public:
    TwoDismensionShape(){
        cout << "TwoDismensionShape" << endl;
    };
    
    ~TwoDismensionShape(){
        cout << "~TwoDismensionShape" << endl;
    };

};

#endif /* TwoDismensionShape_h */
