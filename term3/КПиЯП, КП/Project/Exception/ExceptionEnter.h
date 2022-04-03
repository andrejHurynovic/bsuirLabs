//
//  ExceptionEnter.h
//  LabWork 6. Exception
//
//  Created by Andrej Hurynovič on 10.11.20.
//

#ifndef ExceptionEnter_h
#define ExceptionEnter_h

#include "ExceptionTypes.h"
#include "Date.h"
#include "BinaryTree.h"

class ExceptionEnter: public ExceptionTypes {
public:
    template <typename numberType>
    static numberType NumberData(enum DataType type){
        numberType minimalValue = 0;
        numberType maximalValue = 0;
        
        numberType number;
        bool temp;
        
        switch (type) {
            case boolean:
                minimalValue = 0;
                maximalValue = 1;
                break;
                
                //Human
            case humanEditMenu:
                minimalValue = 0;
                maximalValue = 3;
                break;
                
                //Bachelor
            case bachelorEditMenu:
                minimalValue = 0;
                maximalValue = 6;
                break;
            case markMenu:
                minimalValue = 0;
                maximalValue = 2;
                break;
            case benefitMenu:
                minimalValue = 0;
                maximalValue = 2;
                break;
            case markID:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case benefitID:
                minimalValue = 0;
                maximalValue = -1;
                break;
                
                //Master
            case masterEditMenu:
                minimalValue = 0;
                maximalValue = 7;
                break;

                //Doctor
            case doctorEditMenu:
                minimalValue = 0;
                maximalValue = 8;
                break;
                
                //Date
            case year:
                minimalValue = 1900;
                maximalValue = 2020;
                break;
            case month:
                minimalValue = 1;
                maximalValue = 12;
                break;
            case day:
                minimalValue = 1;
                maximalValue = 31;
                break;
                
                //Mark
            case mark:
                minimalValue = 0;
                maximalValue = 10;
                break;
            case resit:
                minimalValue = 0;
                maximalValue = 1;
                break;
                
                //Benefit
            case benefitType:
                minimalValue = 0;
                maximalValue = 3;
                break;
                
                //Publication
            case accreditation:
                minimalValue = 0;
                maximalValue = 1;
                break;
                
                //Settings
            case settingsMenu:
                minimalValue = 0;
                maximalValue = 3;
                break;
            case numberOfSettings:
                minimalValue = 0;
                maximalValue = 15;
                break;
                
            case bachelorBase:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case masterBase:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case doctorBase:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case benefits:
                minimalValue = 0;
                maximalValue = 1;
                break;
            case disabledBenefit:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case socialBenefit:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case councilBenefit:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case personalBenefit:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case marks:
                minimalValue = 0;
                maximalValue = 1;
                break;
            case markFirst:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case markSecond:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case markThird:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case publication:
                minimalValue = 0;
                maximalValue = 1;
                break;
            case journalAccreditation:
                minimalValue = 0;
                maximalValue = 1;
                break;
            case dissertationComplited:
                minimalValue = 0;
                maximalValue = 1;
                break;
                  
            //Menu
            case studnetTypes:
                minimalValue = 0;
                maximalValue = 3;
                break;
            case menuNumber:
                minimalValue = 0;
                maximalValue = 8;
                break;
            case removeMenu:
                minimalValue = 0;
                maximalValue = 2;
                break;
            case searchMenu:
                minimalValue = 0;
                maximalValue = 5;
                break;
            case scholarshipMenu:
                minimalValue = 0;
                maximalValue = 2;
                break;
            case scholarshipValue:
                minimalValue = 0;
                maximalValue = -1;
                break;
            case sortMenu:
                minimalValue = 0;
                maximalValue = 2;
                break;

            default:
                break;
        }
        
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
                    throw ExceptionTypes(type, "Stream error.");
                }
                
                if(minimalValue != maximalValue){
                    
                    if(number < minimalValue){
                        throw ExceptionTypes(type, "The number is less than required.");
                    }
                    
                    if(minimalValue < maximalValue){
                        if(number > maximalValue){
                            throw ExceptionTypes(type, "The number is greater than required.");
                        }
                    }
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
    
    
    template <typename studentType>
    static bool checkThisID(string ID, BinaryTree<studentType, int> &tree){
        return tree.checkKey(stoi(ID));
    }
    
    
    static string stringData(enum DataType);
    

    static bool onlyLetters(string);
    static bool onlyDigiths(string);
    
};

#endif /* ExceptionEnter_h */
