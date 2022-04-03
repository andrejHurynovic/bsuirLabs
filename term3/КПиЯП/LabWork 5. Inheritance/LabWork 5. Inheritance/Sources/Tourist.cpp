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
    cout << setw(13) << "|  Surname  |" << setw(12) << "|   Name   |" << setw(12) << "| Birthday |"<< setw(16) << "|Pasport number|" << setw(15) << "|   Country   |" << setw(12) << "|   Date   |"  << endl;
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
    
    cout << "Pasport number:" << endl;
    cin >> tourist.pasportNumber;
    
    int temp;
    BorderCrossing borderCrossing;

    do{
        cout << "Enter border crossing? (0/1)";
        cin >> temp;
        
        if(temp){
            cout << "Border crossing:" << endl << "Country:";
            cin >> borderCrossing.country;
            cout << "Date:" << endl;
            cin >> borderCrossing.date;
            
            tourist.borderCrossings.push_back(borderCrossing);
        }
        
    }while(temp);

    return inputStream;
}
