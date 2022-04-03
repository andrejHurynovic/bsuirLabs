//
//  Settings.cpp
//  Project
//
//  Created by Andrej Hurynovič on 13.12.20.
//

#include "Settings.h"


void Settings::getSettingsFromFile(){
    
    File file(settings, false);
    
    file.read(&bachelorBase);
    file.read(&masterBase);
    file.read(&doctorBase);
    file.read(&benefits);
    file.read(&disabledBenefit);
    file.read(&socialBenefit);
    file.read(&councilBenefit);
    file.read(&personalBenefit);
    file.read(&marks);
    file.read(&markFirst);
    file.read(&markSecond);
    file.read(&markThird);
    file.read(&resit);
    file.read(&publication);
    file.read(&journalAccreditation);
    file.read(&dissertationComplited);
}

void Settings::setSettingsToFile(){
    
    File file(settings, true);
    
    file.write(bachelorBase);
    file.write(masterBase);
    file.write(doctorBase);
    file.write(benefits);
    file.write(disabledBenefit);
    file.write(socialBenefit);
    file.write(councilBenefit);
    file.write(personalBenefit);
    file.write(marks);
    file.write(markFirst);
    file.write(markSecond);
    file.write(markThird);
    file.write(resit);
    file.write(publication);
    file.write(journalAccreditation);
    file.write(dissertationComplited);
}

void Settings::setTheDefaultSettings(){
    
    bachelorBase = 100;
    masterBase = 200;
    doctorBase = 400;
    benefits = true;
    disabledBenefit = 1.5;
    socialBenefit = 2;
    councilBenefit = 1.6;
    personalBenefit = 3;
    marks = true;
    markFirst = 1.1;
    markSecond = 1.2;
    markThird = 1.3;
    resit = true;
    publication = true;
    journalAccreditation = true;
    dissertationComplited = true;
    
    setSettingsToFile();
}



void Settings::menu(){
    do{
        cout << "0. Print settings." << endl << "1. Edit settings." << endl << "2. Set the default settings." << endl << "3. Exit." << endl;
        switch(ExceptionEnter::NumberData<int>(DataType::settingsMenu)){
            case 0:
                printSettings();
                break;
            case 1:
                editSettings();
                break;
            case 2:
                setTheDefaultSettings();
                break;
            case 3:
                return;
        }
    }while(true);
}

void Settings::editSettings(){
    cout <<
    "0. Bachelor base scholarship. (0...∞)." << endl <<
    "1. Master base scholarship. (0...∞)." << endl <<
    "2. Вoctor base scholarship. (0...∞)." << endl <<
    "3. Benefits. (0/1):." << endl <<
    "4. Disabled benif. (0...∞)." << endl <<
    "5. Social benefit. (0...∞)." << endl <<
    "6. Council benefit. (0...∞)." << endl <<
    "7. Personal benefit. (0...∞)." << endl <<
    "8. Marks. (0/1)." << endl <<
    "9. Marks first level (7 – 8) (0...∞)." << endl <<
    "10. Marks second level (8 - 9) (0...∞)." << endl <<
    "11. Marks third level (9 - 10) (0...∞)." << endl <<
    "12. Resit. (0/1)." << endl <<
    "13. Publication. (0/1)." << endl <<
    "14. Publication journal accreditation. (0/1)." << endl <<
    "15. Dissertation complited (0/1)." << endl;
    
    int temp = ExceptionEnter::NumberData<int>(numberOfSettings);
    
    cout << "Enter new value: ";
    
    switch (temp) {
        case 0:
            bachelorBase = ExceptionEnter::NumberData<float>(DataType::bachelorBase);
            break;
        case 1:
            masterBase = ExceptionEnter::NumberData<float>(DataType::masterBase);
            break;
        case 2:
            doctorBase = ExceptionEnter::NumberData<float>(DataType::doctorBase);
            break;
        case 3:
            benefits = ExceptionEnter::NumberData<float>(DataType::benefits);
            break;
        case 4:
            disabledBenefit = ExceptionEnter::NumberData<float>(DataType::disabledBenefit);
            break;
        case 5:
            socialBenefit = ExceptionEnter::NumberData<float>(DataType::socialBenefit);
            break;
        case 6:
            councilBenefit = ExceptionEnter::NumberData<float>(DataType::councilBenefit);
            break;
        case 7:
            personalBenefit = ExceptionEnter::NumberData<float>(DataType::personalBenefit);
            break;
        case 8:
            marks = ExceptionEnter::NumberData<float>(DataType::marks);
            break;
        case 9:
            markFirst = ExceptionEnter::NumberData<float>(DataType::markFirst);
            break;
        case 10:
            markSecond = ExceptionEnter::NumberData<float>(DataType::markSecond);
            break;
        case 11:
            markThird = ExceptionEnter::NumberData<float>(DataType::markThird);
            break;
        case 12:
            resit = ExceptionEnter::NumberData<float>(DataType::resit);
            break;
        case 13:
            publication = ExceptionEnter::NumberData<float>(DataType::publication);
            break;
        case 14:
            journalAccreditation = ExceptionEnter::NumberData<float>(DataType::journalAccreditation);
            break;
        case 15:
            dissertationComplited = ExceptionEnter::NumberData<float>(DataType::dissertationComplited);
    }
    
    setSettingsToFile();
    cout << "New value was saved." << endl;
}

void Settings::printSettings(){
    cout <<
    "0. Bachelor base scholarship = " << bachelorBase << endl <<
    "1. Master base scholarship = " << masterBase << endl <<
    "2. Вoctor base scholarship = " << doctorBase << endl <<
    "3. Impact of benefits on the scholarship = " << benefits << endl <<
    "4. Disabled benefit " << disabledBenefit << endl <<
    "5. Social benefit = " << socialBenefit << endl <<
    "6. Council benefit = " << councilBenefit << endl <<
    "7. Personal benefit = " << personalBenefit << endl <<
    "8. Marks = " << marks << endl <<
    "9. Marks first level (7 – 8) = " << markFirst << endl <<
    "10. Marks second level (8 - 9) = " << markSecond << endl <<
    "11. Marks third level (9 - 10) = " << markThird << endl <<
    "12. Resit = " << resit << endl <<
    "13. Publication = " << publication << endl <<
    "14. Publication journal accreditation = " << journalAccreditation << endl <<
    "15. Dissertation complited = " << dissertationComplited << endl << endl;
}


float Settings::getBachelorBase(){
    return bachelorBase;
}

float Settings::getMasterBase(){
    return masterBase;
}

float Settings::getDoctorBase(){
    return doctorBase;
}


bool Settings::getBenefits(){
    return benefits;
}

float Settings::getBenefitByType(enum BenefitType type){
    switch (type) {
        case disabled:
            return disabledBenefit;
            break;
        case social:
            return socialBenefit;
            break;
        case council:
            return councilBenefit;
            break;
        case personal:
            return personalBenefit;
            break;
    }
}

bool Settings::getMarks(){
    return marks;
}

float Settings::getMarkFirst(){
    return markFirst;
}

float Settings::getMarkSecond(){
    return markSecond;
}

float Settings::getMarkThird(){
    return markThird;
}


bool Settings::getResit(){
    return resit;
}


bool Settings::getPublication(){
    return publication;
}

bool Settings::getJournalAccreditation(){
    return journalAccreditation;
}

bool Settings::getDissertationComplited(){
    return dissertationComplited;
}

int Settings::getLength(enum DataType type){
    switch (type) {
        case name:
            return 16;
            break;
        case privateID:
            return 8;
            break;
            
        //Teacher
        case subject:
            return 16;
            break;
            
        //Bachelor
        case group:
            return 6;
            break;
        case scholarship:
            return 11;
            break;
            
        //Date
        case date:
            return 2;
            break;
        case year:
            return 4;
            break;
        case month:
            return 2;
            break;
        case day:
            return 2;
        
        //Mark
        case mark:
            return 4;
            break;
        case DataType::resit:
            return 5;
            break;
            
        //Benefit
        case benefitType:
            return 8;
            break;
            
        //Publication
        case publicationName:
            return 16;
            break;
        case journalName:
            return 16;
            break;
        case accreditation:
            return 13;
            break;
            
        //Doctor
        case DataType::dissertationComplited:
            return 12;
            break;
            
        default:
            return 0;
            break;
    }
}



float Settings::bachelorBase = 100;
float Settings::masterBase = 200;
float Settings::doctorBase = 400;

bool Settings::benefits = true;
float Settings::disabledBenefit = 1.5;
float Settings::socialBenefit = 2;
float Settings::councilBenefit = 1.6;
float Settings::personalBenefit = 3;

bool Settings::marks = true;
float Settings::markFirst = 1.1;
float Settings::markSecond = 1.2;
float Settings::markThird = 1.3;

bool Settings::resit = true;

bool Settings::publication = true;
bool Settings::journalAccreditation = true;

bool Settings::dissertationComplited = true;

