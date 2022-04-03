//
//  ExceptionTypes.h
//  LabWork 6. Exception
//
//  Created by Андрэй Гурыновіч on 10.11.20.
//

#ifndef ExceptionTypes_h
#define ExceptionTypes_h

#include<iostream>
#include<exception>

enum ErrorType{
    bollean,
    surname,
    name,
    day,
    month,
    year,
    passportNumber,
    country,
    licenseNumber,
    address,
    amount,
    purchaseAddressType
};


using namespace std;

class ExceptionTypes {
protected:
    enum ErrorType type;
    string errorMessage;
    string userMessage;
public:
    ExceptionTypes(enum ErrorType type, string string = ""){
        this->type = type;
        this->userMessage = string;
        
        switch (type) {
            case bollean:
                errorMessage = "bollean";   // 0/1
                break;
            case day:
                errorMessage = "day";       //[1; 31]
                break;
            case month:
                errorMessage = "month";     //[1; 12]
                break;
            case year:
                errorMessage = "year";      //[-9999; 2020]
                break;
            case name:
                errorMessage = "name";
                break;
            case surname:
                errorMessage = "surname";
                break;
            case passportNumber:
                errorMessage = "passport number";   //[AA1111111]
                break;
            case country:
                errorMessage = "country";
                break;
            case licenseNumber:
                errorMessage = "licenseNumber";
                break;
            case address:
                errorMessage = "address";
                break;
            case amount:
                errorMessage = "amount";
                break;
            case purchaseAddressType:
                errorMessage = "purchase address";
                break;
        }
    }
    
    string getErrorTypeString();
    
    string getUserMessage();
    
    static void Terminate();
    
    ~ExceptionTypes(){
    }
};

#endif /* ExceptionTypes_h */
