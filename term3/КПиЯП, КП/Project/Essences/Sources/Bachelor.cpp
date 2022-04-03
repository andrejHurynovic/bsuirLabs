//
//  Bachelor.cpp
//  Project
//
//  Created by Andrej Hurynovič on 13.12.20.
//

#include "Bachelor.h"
#include "Algorithms.h"

void Bachelor::writeToFile(File& file){
    Algorithms::writeBachelorToFile(*this, file);
}

void Bachelor::readFromFile(File& file){
    Human::readFromFile(file);
    
    file.read(&group);
    file.read(&scholarship);
    
    
    unsigned long marksSize;
    file.read(&marksSize);
    
    Mark mark;
    for(int i = 0; i < marksSize; i++){
        file.read(&mark);
        marks.push_back(mark);
    }
    
    unsigned long benefitsSize;
    file.read(&benefitsSize);
    
    Benefit benefit;
    for(int i = 0; i < benefitsSize; i++){
        file.read(&benefit);
        benefits.push_back(benefit);
    }
}




void Bachelor::calculateScholarship(float base){
    scholarship = Algorithms::calclulateBachelorScholarship(*this, base);
}



string Bachelor::getGroup(){
    return group;
}

float Bachelor::getScholarship(){
    return scholarship;
}
bool Bachelor::getShowScholarship(){
    return showScholarship;
}

Mark* Bachelor::getMarkForID(int ID){
    if(this->marks.size() <= ID){
        return NULL;
    }
    return &marks[ID];
}

unsigned long Bachelor::getMarksSize(){
    return marks.size();
}


Benefit* Bachelor::getBenefitForID(int ID){
    if(this->benefits.size() <= ID){
        return NULL;
    }
    return &benefits[ID];
}

unsigned long Bachelor::getBenefitsSize(){
    return benefits.size();
}




void Bachelor::setGroup(string group){
    this->group = group;
}

void Bachelor::setScholarship(float scholarship){
    this->scholarship = scholarship;
}
void Bachelor::setShowScholarship(bool showScholarship){
    this->showScholarship = showScholarship;
}

void Bachelor::addMark(Mark mark){
    marks.push_back(mark);
}

void Bachelor::addBenefit(Benefit benefit){
    benefits.push_back(benefit);
}



void Bachelor::removeMarkForID(int ID){
    if(this->marks.size() <= ID){
        cout << "No such ID." << endl;
        return;
    }else{
        cout << "The value was successfully removed." << endl;
    }
    
    marks.erase(marks.begin()+ID);
}

void Bachelor::removeBenefitForID(int ID){
    if(this->benefits.size() <= ID){
        cout << "No such ID." << endl;
        return;
    }else{
        cout << "The value was successfully removed." << endl;
    }
    
    benefits.erase(benefits.begin()+ID);
}



void Bachelor::editMenu(bool getValue){
    do{
        Human::editMenu(false);
        cout <<
        "4. Group." << endl <<
        "5. Mark. " << endl <<
        "6. Benefit. " << endl;
        
        if(getValue){
            cout << "0. Exit." << endl;
            
            int value = ExceptionEnter::NumberData<int>(bachelorEditMenu);
            
            if(!value){
                return;
            }
            
            edit(value);
        }else{
            return;
        }
        
    }while(true);
}

void Bachelor::edit(int key){
    if(key < 4){
        Human::edit(key);
    }else{
        switch (key) {
            case 4:
                cout << "Enter new value: " << endl;
                group = ExceptionEnter::stringData(DataType::group);
                break;
            case 5:{
                if(marks.empty()){
                    cout << "No marks, enter new one." << endl;
                    Mark mark;
                    cin >> mark;
                    addMark(mark);
                }else{
                    do{
                        if(marks.empty()){
                            cout << "All marks was deleted." << endl;
                            
                            return;
                        }
                        
                        Mark::printSpreadsheet();
                        cout << endl;
                        
                        for(int i = 0; i < marks.size(); i++){
                            cout << '|' << marks[i] << endl;
                        }
                        
                        cout << endl <<
                        "1. Add." << endl <<
                        "2. Remove." << endl <<
                        "0. Exit." << endl;
                        
                        switch (ExceptionEnter::NumberData<int>(markMenu)) {
                            case 0:
                                
                                return;
                            case 1:{
                                cout << "Enter new value: " << endl;
                                Mark mark;
                                cin >> mark;
                                addMark(mark);
                                break;
                            }
                            case 2:
                                if(marks.size() == 1){
                                    cout << "For the calculation, the student must have at least one mark." << endl;
                                    continue;
                                }
                                cout << "Choose number: " << endl;
                                removeMarkForID(ExceptionEnter::NumberData<int>(markID));

                        }
                    }while(true);
                    
                }
                break;
            }
            case 6:{
                if(benefits.empty()){
                    cout << "No benefits, enter new one." << endl;
                    Benefit benefit;
                    cin >> benefit;
                    addBenefit(benefit);
                }else{
                    do{
                        if(benefits.empty()){
                            cout << "All benefits was deleted." << endl;
                            return;
                        }
                        
                        cout << '|' << setw(Settings::getLength(DataType::benefitType)) << "Benefit" << '|' << endl;
                        
                        for(int i = 0; i < benefits.size(); i++){
                            cout << '|' << benefits[i] << '|' << endl;
                        }
                        
                        cout << endl <<
                        "1. Add." << endl <<
                        "2. Remove." << endl <<
                        "0. Exit." << endl;
                        
                        switch (ExceptionEnter::NumberData<int>(benefitMenu)) {
                            case 0:
                                
                                return;
                            case 1:{
                                Benefit benefit;
                                bool error = false;
                                cin >> benefit;
                                
                                for(int i = 0; i < benefits.size(); i++){
                                    if(benefit == benefits[i]){
                                        cout << "You can't add two identical benefits." << endl;
                                        error = true;
                                    }
                                }
                                if(!error){
                                    addBenefit(benefit);
                                }
                                
                                break;
                            }
                            case 2:
                                cout << "Choose number: " << endl;
                                removeBenefitForID(ExceptionEnter::NumberData<int>(benefitID));
                        }
                    }while(true);
                }                
                break;
            }
        }
        
    }
}


void Bachelor::printMarksAndBenefits(){
    
    if(marks.size() <= 1 && benefits.size() <= 1){
        return;
    }
    
    int markNumber = 1;
    int benefitNumber = 1;
    
    do{
        cout << setw(Settings::getLength(DataType::privateID) +
                     Settings::getLength(DataType::name) +
                     Settings::getLength(DataType::year) +
                     Settings::getLength(DataType::month) +
                     Settings::getLength(DataType::day) + 2 + 6 +
                     Settings::getLength(DataType::group) + 2) << ' ';
        
        if(marks.size() > markNumber){
            cout << '|' << marks[markNumber++];
        }else{
            cout << setw(Settings::getLength(DataType::subject) + Settings::getLength(DataType::mark) + Settings::getLength(DataType::resit) + 7);
        }
        
        if(benefits.size() > benefitNumber){
            cout << '|' << benefits[benefitNumber++] << '|';
        }
        
        cout << endl;
        
    }while(marks.size() > markNumber || benefits.size() > benefitNumber);
    
}

void Bachelor::printSpreadsheet(bool scholarship){
    Human::printSpreadsheet();
    
    cout <<
    '|' << setw(Settings::getLength(DataType::group)) << "Group" << '|' <<
    '|' << setw(Settings::getLength(DataType::subject)) << "Subject" << '|' <<
    '|' << setw(Settings::getLength(DataType::mark)) << "Mark" << '|' <<
    '|' << setw(Settings::getLength(DataType::resit)) << "Resit" << '|' <<
    '|' << setw(Settings::getLength(DataType::benefitType)) << "Benefit" << '|';
    if(scholarship){
        cout << '|' << setw(Settings::getLength(DataType::scholarship)) << "Scholarship" << '|';
    }
}

ostream& operator << (ostream &stream, Bachelor bachelor){
    
    cout << *dynamic_cast<Human*>(&bachelor) <<
    '|' << bachelor.group << '|' <<
    '|' << bachelor.marks[0] << '|';
    
    if(bachelor.benefits.size()){
        cout << bachelor.benefits[0] << '|';
    }else{
        cout << setw (Settings::getLength(benefitType)) << ' ' << '|';
    }
    
    if(bachelor.showScholarship){
        cout << '|' << setw(Settings::getLength(DataType::scholarship)) << bachelor.scholarship << '|';
    }
    
    return stream;
}

istream& operator >> (istream &stream, Bachelor &bachelor){
    
    cin >> *dynamic_cast<Human*>(&bachelor);
    
    cout << endl << "Enter group (" << Settings::getLength(DataType::group) << " digits): " << endl;
    
    bachelor.group = ExceptionEnter::stringData(DataType::group);
    
    cout << endl << "Enter mark: " << endl;
    
    Mark mark;
    cin >> mark;
    
    bachelor.addMark(mark);
    
    cout << endl << "Add one more? (0/1): ";
    
    while (ExceptionEnter::NumberData<int>(boolean)) {
        cin >> mark;
        bachelor.addMark(mark);
        cout << endl << "Add one more? (0/1): ";
    }
    
    cout << endl << "Does the student have benefits? (0/1): ";
    
    if(ExceptionEnter::NumberData<int>(boolean)){
        Benefit benefit;
        cin >> benefit;
        
        bachelor.addBenefit(benefit);
        
        cout << endl << "Add one more? (0/1): ";
        
        while (ExceptionEnter::NumberData<int>(boolean)) {
            bool error = false;
            cin >> benefit;
            
            for(int i = 0; i < bachelor.benefits.size(); i++){
                if(benefit == bachelor.benefits[i]){
                    cout << "You can't add two identical benefits." << endl << endl << "Add one more? (0/1): ";
                    error = true;
                    break;
                }
            }
            
            if(error){
                continue;
            }
            
            bachelor.addBenefit(benefit);
            cout << endl << "Add one more? (0/1): ";
        }
    }
    
    return stream;
}

