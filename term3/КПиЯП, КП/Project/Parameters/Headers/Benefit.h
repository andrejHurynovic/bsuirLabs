//
//  Benefit.h
//  Project
//
//  Created by Andrej Hurynovič on 27.10.20.
//

#ifndef Benefit_h
#define Benefit_h

#include <iostream>
#include "ExceptionEnter.h"


using namespace std;

enum BenefitType{
    disabled,
    social,
    council,
    personal
};



class Benefit {
protected:
    enum BenefitType type;
    
public:
    Benefit(BenefitType type = disabled){
        this->type = type;
    }
    
    enum BenefitType getType();
    float getModifier();
    
    void setType(enum BenefitType);
    
    bool operator == (const Benefit &benefit);
    
    friend ostream& operator << (ostream &stream, Benefit benefit);
    friend istream& operator >> (istream &stream, Benefit &benefit);
    
    ~Benefit(){};
};

#endif /* Benefit_h */
