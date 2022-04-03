//
//  ExceptionTypes.h
//  LabWork 6. Exception
//
//  Created by Andrej Hurynovič on 10.11.20.
//

#ifndef ExceptionTypes_h
#define ExceptionTypes_h

#include<iostream>
#include<exception>

enum DataType{
    boolean,
    
    //Human
    name,
    privateID,
    humanEditMenu,
    
    //Bachelor
    group,
    bachelorEditMenu,
    scholarship,
    
    //Master
    masterEditMenu,

    //Doctor
    doctorEditMenu,
    
    //Date
    date,
    year,
    month,
    day,
    
    //Mark
    mark,
    resit,
    subject,
    markMenu,
    markID,
    
    //Benefit
    benefitType,
    benefitMenu,
    benefitID,
    
    //Publication
    publicationName,
    journalName,
    accreditation,
    
    //Settings
    settingsMenu,
    numberOfSettings,
    bachelorBase,
    masterBase,
    doctorBase,
    benefits,
    disabledBenefit,
    socialBenefit,
    councilBenefit,
    personalBenefit,
    marks,
    markFirst,
    markSecond,
    markThird,
    publication,
    journalAccreditation,
    dissertationComplited,

    
    //File
    settingsFile,
    
    //Menu
    studnetTypes,
    removeMenu,
    searchMenu,
    menuNumber,
    scholarshipMenu,
    scholarshipValue,
    sortMenu,
};


using namespace std;

class ExceptionTypes {
protected:
    enum DataType type;
    string errorMessage;
    string userMessage;
public:
    ExceptionTypes(enum DataType type, string string = ""){
        this->type = type;
        this->userMessage = string;
        
        switch (type) {
            case boolean:
                errorMessage = "IDKNRN";
                break;
                
                //Human
            case name:
                errorMessage = "name";
                break;
            case privateID:
                errorMessage = "private id";
                break;
            case humanEditMenu:
                errorMessage = "human edit menu";
                break;

                //Bachelor
            case bachelorEditMenu:
                errorMessage = "bachelor edit menu";
                break;
            case scholarship:
                errorMessage = "scholarship";
                break;
            case markMenu:
                errorMessage = "mark menu";
                break;
            case benefitMenu:
                errorMessage = "benefit menu";
                break;
            case markID:
                errorMessage = "mark ID";
                break;
            case benefitID:
                errorMessage = "benefit ID";
                break;
                
                
                
                //Master
            case masterEditMenu:
                errorMessage = "master edit menu";
                break;
                
                //Doctor
            case doctorEditMenu:
                errorMessage = "doctor edit menu";
                break;
                
                //Date
            case group:
                errorMessage = "group";
                break;
            case date:
                errorMessage = "date";
                break;
            case year:
                errorMessage = "year";
                break;
            case month:
                errorMessage = "month";
                break;
            case day:
                errorMessage = "day";
                break;
            
            //Mark
            case mark:
                errorMessage = "mark";
                break;
            case resit:
                errorMessage = "resit";
                break;
            case subject:
                errorMessage = "subject name";
                break;
                
            //Benefit
            case benefitType:
                errorMessage = "benefit type";
                break;
                
            //Publication
            case publicationName:
                errorMessage = "publication name";
                break;
            case journalName:
                errorMessage = "journal name";
                break;
            case accreditation:
                errorMessage = "accreditation";
                break;
                
            //Settings
            case settingsMenu:
                errorMessage = "settings menu";
                break;
            case numberOfSettings:
                errorMessage = "number of settings";
                break;
            case bachelorBase:
                errorMessage = "bachelor base scholarship";
                break;
            case masterBase:
                errorMessage = "master base scholarship";
                break;
            case doctorBase:
                errorMessage = "doctor base scholarship";
                break;
            case benefits:
                errorMessage = "impact of benefits on the scholarship";
                break;
            case disabledBenefit:
                errorMessage = "disabled";
                break;
            case socialBenefit:
                errorMessage = "social benefit";
                break;
            case councilBenefit:
                errorMessage = "council benefit";
                break;
            case personalBenefit:
                errorMessage = "personal benefit";
                break;
            case marks:
                errorMessage = "marks";
                break;
            case markFirst:
                errorMessage = "marks first level (7 – 8)";
                break;
            case markSecond:
                errorMessage = "marks second level (8 - 9)";
                break;
            case markThird:
                errorMessage = "marks third level (9 - 10)";
                break;
            case publication:
                errorMessage = "publication";
                break;
            case journalAccreditation:
                errorMessage = "publication journal accreditation";
                break;
            case dissertationComplited:
                errorMessage = "dissertation complited";
                break;
                
            //File
            case settingsFile:
                errorMessage = "settings file";
                break;
            
            //Menu
            case studnetTypes:
                errorMessage = "studnet types";
                break;
            case menuNumber:
                errorMessage = "menu number";
                break;
            case removeMenu:
                errorMessage = "remove menu";
                break;
            case searchMenu:
                errorMessage = "search menu";
                break;
            case scholarshipMenu:
                errorMessage = "scholarship menu";
                break;
            case scholarshipValue:
                errorMessage = "scholarship value";
                break;
            case sortMenu:
                errorMessage = "sort menu";
                break;
        }
    }
    
    string getErrorTypeString();
    
    string getUserMessage();
    
    static void Terminate();
    
    ~ExceptionTypes(){}
};

#endif /* ExceptionTypes_h */
