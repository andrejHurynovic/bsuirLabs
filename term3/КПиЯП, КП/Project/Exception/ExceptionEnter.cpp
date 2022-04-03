//
//  ExceptionEnter.cpp
//  LabWork 6. Exception
//
//  Created by Andrej Hurynovič on 10.11.20.
//

#include "ExceptionEnter.h"
#include "Settings.h"


string ExceptionEnter::stringData(enum DataType type){
    
    int requiredLength = 0;
    int maximalLength = 0;
    
    string string;
    bool temp;
    
    switch (type) {
        //Human
        case name:
            maximalLength = Settings::getLength(name);
            break;
        case privateID:
            requiredLength = Settings::getLength(privateID);
            break;
            
        //Teacher
        case subject:
            maximalLength = Settings::getLength(subject);
            break;
            
         //Bachelor
        case group:
            requiredLength = Settings::getLength(group);
            break;
            
        //Publication
        case publicationName:
            maximalLength = Settings::getLength(publicationName);
            break;
        case journalName:
            maximalLength = Settings::getLength(journalName);
            break;
            
        default:
            break;
    }
    
    do{
        temp = false;
        try {
            
            set_terminate(Terminate);
            
            try {
                getline(cin, string);
            } catch (const std::overflow_error& exception) {
                cout << exception.exception::what();
            }
            
            if(cin.fail()){
                throw ExceptionTypes(type, "Stream fail.");
            }
            
            if(maximalLength){
                if(string.length() > maximalLength){
                    throw ExceptionTypes(type, "The string is longer than required.");
                }
            }
            
            if(requiredLength){
                if(string.length() > requiredLength){
                    throw ExceptionTypes(type, "The string is longer than required.");
                }
                if(string.length() < requiredLength){
                    throw ExceptionTypes(type, "The string is shorter than required.");
                }
            }
            
            switch (type) {
                case name:
                        if(!onlyLetters(string)){
                            throw ExceptionTypes(type, "The name must consist only of letters.");
                        }
                    break;
                case subject:
                    if(!onlyLetters(string)){
                        throw ExceptionTypes(type, "The name must consist only of letters.");
                    }
                    break;
                case group:
                    if(!onlyDigiths(string)){
                        throw ExceptionTypes(type, "The name must consist only of digits.");
                    }
                    break;
                case privateID:
                    if(!onlyDigiths(string)){
                        throw ExceptionTypes(type, "The name must consist only of digits.");
                    }
                    break;
                    
                default:
                    break;
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
    
    return string;
}


bool ExceptionEnter::onlyLetters(string string){
    for(int i = 0; i < string.length(); i++){
        if((string[i] < 'A' || string[i] > 'Z') && (string[i] < 'a' || string[i] > 'z')){
            return false;
        }
    }
    return true;
}

bool ExceptionEnter::onlyDigiths(string string){
    for(int i = 0; i < string.length(); i++){
        if((string[i] < '0' || string[i] > '9')){
            return false;
        }
    }
    return true;
}
