//
//  main.cpp
//  LabWork 4. Shapes
//
//  Created by Андрэй Гурыновіч on 22.09.20.
//

#include <iostream>
#include <iomanip>

#include <string>
#include <vector>

#include "ShapesLibrary.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Shape* shapes[6];
   // Circle obj(3);
    shapes[0] = new Circle(3);
    shapes[1] = new Square(3);
    shapes[2] = new Rectangle(3, 4);
    shapes[3] = new Parallelepiped(3, 4, 5);
    shapes[4] = new Cube(3);
    shapes[5] = new Sphere(3);

    
    for(int i = 0; i < 6; i++){
        cout << setw(14) << shapes[i]->getName() << ". Area: " << setw(10) << shapes[i]->getArea() << " Volume: " << shapes[i]->getVolume() << endl;
        delete shapes[i];
    }
    
}
