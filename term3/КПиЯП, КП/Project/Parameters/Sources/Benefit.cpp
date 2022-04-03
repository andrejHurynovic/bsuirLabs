//
//  Benefit.cpp
//  Project
//
//  Created by Andrej Hurynovič on 13.12.20.
//

#include "Benefit.h"
#include "Settings.h"


enum BenefitType Benefit::getType(){
    return this->type;
}

float Benefit::getModifier(){
    return Settings::getBenefitByType(this->type);
}

void Benefit::setType(enum BenefitType type){
    this->type = type;
}



bool Benefit::operator == (const Benefit &benefit){
    if(this->type == benefit.type){
        return true;
    }else{
        return false;
    }
}

ostream& operator << (ostream &stream, Benefit benefit){
    cout << setw (Settings::getLength(benefitType));
    switch (benefit.type) {
        case disabled:
            cout << "Disabled";
            break;
        case social:
            cout << "Social";
            break;
        case council:
            cout << "Council";
            break;
        case personal:
            cout << "Personal";
            break;
    }
    
    return stream;
}

istream& operator >> (istream &stream, Benefit &benefit){
    cout << "Choose benefit type: type (mofifier)" << endl
    << "0. Disabled ("<< Settings::getBenefitByType(disabled) <<")" << endl
    << "1. Social ("<< Settings::getBenefitByType(social) <<")" << endl
    << "2. Concil ("<< Settings::getBenefitByType(council) <<")" << endl
    << "3. Personal ("<< Settings::getBenefitByType(personal) <<")" << endl;
   
    switch (ExceptionEnter::NumberData<int>(benefitType)) {
        case 0:
            benefit.type = disabled;
            break;
        case 1:
            benefit.type = social;
            break;
        case 2:
            benefit.type = council;
            break;
        case 3:
            benefit.type = personal;
            break;
    }
    
    return stream;
}
