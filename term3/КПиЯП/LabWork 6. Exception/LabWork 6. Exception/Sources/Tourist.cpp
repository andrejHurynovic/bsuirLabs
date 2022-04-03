//
//  Tourist.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Tourist.hpp"


void Tourist::setPasportNumber(string pasportNumber){
    this->pasportNumber = pasportNumber;
}

void Tourist::setBorderCrossings(vector<BorderCrossing> borderCrossings){
    this->borderCrossings = borderCrossings;
}

void Tourist::addBorderCrossing(BorderCrossing borderCrossing){
    this->borderCrossings.push_back(borderCrossing);
}

string Tourist::getPasportNumber(){
    return this->pasportNumber;
}

vector<BorderCrossing> Tourist::getBorderCrossings(){
    return borderCrossings;
}

BorderCrossing Tourist::getBorderCrossingForID(int ID){
    if(borderCrossings.size() < ID){
        return borderCrossings[ID];
    }else{
        return BorderCrossing("NO BORDER CROSSING", Date(0,0,0));
    }
}

void Tourist::printSpreadsheet(){
    cout << "|  Surname  |" << "|   Name   |" << "| Birthday |" << "|Pasport number|" << "|   Country   |" << "|   Date   |"  << endl;
}


ostream& operator << (ostream &outputStream, Tourist tourist){
    
    Human *human;
    human = &tourist;
    
    cout << *dynamic_cast<Human*>(human);
    
    cout << '|' << setw(14) << tourist.pasportNumber << '|';
    
    for(int i = 0; i < tourist.borderCrossings.size(); i++){
        if(i){
            cout << setw(54);
        }
        cout << '|' << setw(13) << tourist.borderCrossings[i].country << tourist.borderCrossings[i].date << endl;
    }
    
    return outputStream;
}

istream& operator >> (istream &inputStream, Tourist &tourist){
    Human *human;
    human = &tourist;
    
    cin >> *dynamic_cast<Human*>(human);
    
    cout << "Pasport number(AA1234567): ";
    tourist.pasportNumber = ExceptionEnter::EnterStringWithCheck(passportNumber, 9);
    
    int temp;
    BorderCrossing borderCrossing;

    do{
        cout << "Enter border crossing? (0/1)";
        cin >> temp;
        
        if(temp){
            cout << "Border crossing:" << endl << "Country(max 13 symbols):";
            borderCrossing.country = ExceptionEnter::EnterStringWithCheck(country, 13);
            cout << "Date:" << endl;
            cin >> borderCrossing.date;
            
            tourist.borderCrossings.push_back(borderCrossing);
        }
        
    }while(temp);

    return inputStream;
}
