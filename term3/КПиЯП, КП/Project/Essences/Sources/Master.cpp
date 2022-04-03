//
//  Master.cpp
//  Project
//
//  Created by Andrej Hurynovič on 17.12.20.
//

#include "Master.h"

void Master::writeToFile(File& file){
    Bachelor::writeToFile(file);
    
    
    bool havePublication;
    if(publication){
        havePublication = true;
        file.write(havePublication);
        
        file.write(*(publication));
    }else{
        havePublication = false;
        file.write(havePublication);
    }
}

void Master::readFromFile(File& file){
    Bachelor::readFromFile(file);
    
    bool havePublication;
    file.read(&havePublication);
    
    if(havePublication){
        publication = new Publication();
        file.read(publication);
    }else{
        publication = NULL;
    }
}



void Master::calculateScholarship(float base){
    Bachelor::calculateScholarship(base);
    
    if(Settings::getPublication() && !this->publication){
        scholarship = 0;
    }
}

Publication* Master::getPublication(){
    return this->publication;
}

void Master::setPublication(Publication* publication){
    this->publication = publication;
}

void Master::editMenu(bool getValue){
    do{
        Bachelor::editMenu(false);
        cout <<
        "7. Publication. " << endl;
        
        if(getValue){
            cout << "0. Exit." << endl;
            
            int value = ExceptionEnter::NumberData<int>(masterEditMenu);
            
            if(!value){
                return;
            }
            
            edit(value);
        }else{
            return;
        }
    }while(true);
}

void Master::edit(int key){
    if(key < 7){
        Bachelor::edit(key);
    }else{
        cout << "Enter new value: " << endl;
        switch (key) {
            case 7:
                if(!publication){
                    publication = new Publication();
                }
                cin >> *publication;
                
                break;
        }
    }
}

void Master::printSpreadsheet(bool scholarship){
    Bachelor::printSpreadsheet(false);
    cout <<
    '|' << setw(Settings::getLength(DataType::publicationName)) << "Publication" << '|' <<
    '|' << setw(Settings::getLength(DataType::journalName)) << "Journal name" << '|' <<
    '|' << setw(Settings::getLength(DataType::accreditation)) << "Accreditation" << '|';
    if(scholarship){
        cout << '|' << setw(Settings::getLength(DataType::scholarship)) << "Scholarship" << '|';
    }
}


ostream& operator << (ostream &stream, Master master){
    
    if(master.showScholarship){
        master.showScholarship = false;
        cout << *dynamic_cast<Bachelor*>(&master);
        master.showScholarship = true;
    }else{
        cout << *dynamic_cast<Bachelor*>(&master);
    }


    
    if(master.publication){
        cout << *(master.publication);
    }else{
        cout << setw(Settings::getLength(DataType::publicationName) + Settings::getLength(DataType::journalName) + Settings::getLength(DataType::accreditation) + 6) << '|';
    }
    
    if(master.showScholarship){
        cout << '|' << setw(Settings::getLength(DataType::scholarship)) << master.scholarship << '|';
    }
    
    return stream;
}

istream& operator >> (istream &stream, Master &master){
    
    cin >> *dynamic_cast<Bachelor*>(&master);
    
    cout << endl << "Does the student have publication? (0/1): ";
    if(ExceptionEnter::NumberData<int>(boolean)){
        master.publication = new Publication();
        
        cin >> *(master.publication);
    }
    
    return stream;
}
