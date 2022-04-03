//
//  Tourist.hpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef Tourist_hpp
#define Tourist_hpp

#include "Human.hpp"
#include "BorderCrossing.h"
#include <vector>

#include "ExceptionEnter.hpp"

class Tourist: public virtual Human{
protected:
    string pasportNumber;
    vector<BorderCrossing> borderCrossings;
public:
    Tourist(string pasportNumber = "NULL", vector<BorderCrossing> borderCrossings = vector<BorderCrossing>()){
        this->pasportNumber = pasportNumber;
        this->borderCrossings = borderCrossings;
    }
    
    void setPasportNumber(string pasportNumber);
    
    void setBorderCrossings(vector<BorderCrossing> borderCrossings);
    
    void addBorderCrossing(BorderCrossing borderCrossing);
    
    string getPasportNumber();
    
    vector<BorderCrossing> getBorderCrossings();
    
    BorderCrossing getBorderCrossingForID(int ID);
    
    void printSpreadsheet();
    
    friend ostream& operator << (ostream &outputStream, Tourist tourist);
    friend istream& operator >> (istream &inputStream, Tourist &Tourist);
    
    ~Tourist(){
        borderCrossings.clear();
    };
};

#endif /* Tourist_hpp */
