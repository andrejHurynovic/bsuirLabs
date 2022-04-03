//
//  Doctor.cpp
//  Project
//
//  Created by Andrej Hurynovič on 17.12.20.
//

#include "Doctor.h"

void Doctor::writeToFile(File& file){
    Master::writeToFile(file);

    file.write(dissertationComplited);
}

void Doctor::readFromFile(File& file){
    Master::readFromFile(file);

    file.read(&dissertationComplited);
}



void Doctor::calculateScholarship(float base){
    Master::calculateScholarship(base);
    
    if(Settings::getJournalAccreditation() && (!this->publication || !this->publication->getAccreditation())){
        scholarship = 0;
    }
    
    if(Settings::getDissertationComplited() && !this->dissertationComplited){
        scholarship = 0;
    }
}

bool Doctor::getDissertationComplited(){
    return this->dissertationComplited;
}

void Doctor::setDissertationComplited(bool dissertationComplited){
    this->dissertationComplited = dissertationComplited;
}

void Doctor::editMenu(bool getValue){
    do{
    Master::editMenu(false);
    cout <<
    "8. Dissertation complition. " << endl;
        
        if(getValue){
            cout << "0. Exit." << endl;
            
            int value = ExceptionEnter::NumberData<int>(doctorEditMenu);
            
            if(!value){
                return;
            }
            
            edit(value);
        }else{
            return;
        }
    }while(true);
}

void Doctor::edit(int key){
    if(key < 8){
        Master::edit(key);
    }else
        cout << "Enter new value: " << endl;
    switch (key) {
        case 8:
            dissertationComplited = ExceptionEnter::NumberData<int>(DataType::dissertationComplited);
            
            break;
    }
}

void Doctor::printSpreadsheet(bool scholarship){
    Master::printSpreadsheet(false);
    cout << '|' << setw(Settings::getLength(DataType::dissertationComplited)) << "Dissertation" << '|';
    if(scholarship){
        cout << '|' << setw(Settings::getLength(DataType::scholarship)) << "Scholarship" << '|';
    }
}

ostream& operator << (ostream &stream, Doctor doctor){
    
    if(doctor.showScholarship){
        doctor.showScholarship = false;
        cout << *dynamic_cast<Master*>(&doctor);
        doctor.showScholarship = true;
    }else{
        cout << *dynamic_cast<Master*>(&doctor);
    }
        
    cout << '|' << setw(Settings::getLength(DataType::dissertationComplited)) << doctor.dissertationComplited << '|';
    
    if(doctor.showScholarship){
        cout << '|' << setw(Settings::getLength(DataType::scholarship)) << doctor.scholarship << '|';
    }
    
    return stream;
}
istream& operator >> (istream &stream, Doctor &doctor){
    
    cin >> *dynamic_cast<Master*>(&doctor);
    
    cout << endl << "Does this student completed dissertation? (0/1): ";
    doctor.dissertationComplited = ExceptionEnter::NumberData<int>(boolean);

    return stream;
}
