//
//  ExceptionTypes.cpp
//  LabWork 6. Exception
//
//  Created by Андрэй Гурыновіч on 10.11.20.
//

#include "ExceptionTypes.h"

string ExceptionTypes::getErrorTypeString(){
    return errorMessage;
}

string ExceptionTypes::getUserMessage(){
    return userMessage;
}

void ExceptionTypes::Terminate(){
    cout << "Terminate called";
}



