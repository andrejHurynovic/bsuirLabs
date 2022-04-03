//
//  ExceptionEnter.cpp
//  LabWork 6. Exception
//
//  Created by Андрэй Гурыновіч on 10.11.20.
//

#include "ExceptionEnter.hpp"

int ExceptionEnter::EnterIntWithCheck(enum ErrorType type, int minimal, int maximal){
    int number;
    bool temp;
    
    do{
        temp = false;
        
        try {
            
            set_terminate(Terminate);
            
            try {
                cin >> number;
            } catch (const std::overflow_error& exception) {
                cout << exception.exception::what();
            }
           
            if(cin.fail() || cin.get() != '\n'){
                throw ExceptionTypes(type, "Stream error");
            }
            if(number < minimal || number > maximal ){
                throw ExceptionTypes(type, "Out of range");
            }
            
        } catch (ExceptionTypes& exception) {
            cin.clear();
            rewind (stdin);
            cout << "Please correct error in " << exception.getErrorTypeString() << ':' << endl << exception.getUserMessage() << endl;
            
            temp = true;
        }
        catch(...){
            cout << "Unknown error";
            cin.clear();
            rewind(stdin);
        }
    }while(temp);
    
    return number;
}

string ExceptionEnter::EnterStringWithCheck(enum ErrorType type, int maximalLenght){
    string string;
    bool temp;
    
    do{
        temp = false;
        try {
            
            set_terminate(Terminate);
            
//            try {
                cin >> string;
//            } catch (const std::overflow_error& exception) {
//                cout << exception.exception::what();
//            }
            
            if(cin.fail()){
                throw ExceptionTypes(type, "Stream fail");
            }
           
            if((maximalLenght != 0 && string.length() > maximalLenght)){
                throw ExceptionTypes(type, "Out of range");
            }
            
            switch (type) {
                case passportNumber:
                    for(int i = 0; i < 9; i++){
                        if(i < 2 && (string[i] < 'A' || string[i] > 'Z')){
                            throw ExceptionTypes(type, "Format error");
                        }
                        if(i > 1 && (string[i] < '1' || string[i] > '9')){
                            throw ExceptionTypes(type, "Format error");
                        }
                    }
                    break;
                default:
                    break;
            }
            
        } catch (ExceptionTypes& exception) {
            cin.clear();
//            rewind stdin;
            cout << "Please correct error in " << exception.getErrorTypeString() << ':' << endl << exception.getUserMessage() << endl;

            
            temp = true;
            
        }
        catch(...){
            cout << "Unknown error";
            cin.clear();
            rewind(stdin);
        }
    }while(temp);
    
    return string;
}

