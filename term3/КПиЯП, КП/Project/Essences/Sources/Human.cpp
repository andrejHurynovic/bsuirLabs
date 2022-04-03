//
//  Human.cpp
//  Project
//
//  Created by Andrej Hurynovič on 12.12.20.
//

#include "Human.h"

void Human::writeToFile(File& file){
    file.write(privateID);
    file.write(name);
    file.write(birthday);
}

void Human::readFromFile(File& file){
    file.read(&privateID);
    file.read(&name);
    file.read(&birthday);
    
}


string Human::getPrivateID(){
    return this->privateID;
}

string Human::getName(){
    return this->name;
}

Date Human::getBirthday(){
    return this->birthday;
}

void Human::setPrivateID(string privateID){
    this->privateID = privateID;
}
void Human::setName(string name){
    this->name = name;
}

void Human::setBirthday(Date birthday){
    this->birthday = birthday;
}





void Human::editMenu(bool getValue){
    do{
        cout << endl <<
        "1. Private ID." << endl <<
        "2. Name. " << endl <<
        "3. Birthday. " << endl;
        
        if(getValue){
            cout << "0. Exit." << endl;
            
            int value = ExceptionEnter::NumberData<int>(humanEditMenu);
            
            if(!value){
                return;
            }
            
            edit(value);
        }else{
            return;
        }
    }while(true);
}

void Human::edit(int key){
    
    cout << "Enter new value: " << endl;
    switch (key) {
        case 1:
            privateID = ExceptionEnter::stringData(DataType::privateID);
            break;
        case 2:
            name = ExceptionEnter::stringData(DataType::name);
            break;
        case 3:
            cin >> birthday;
            break;
    }
}



void Human::printSpreadsheet(){
    cout <<
    '|' << setw(Settings::getLength(DataType::privateID)) << "ID" << '|' <<
    '|' << setw(Settings::getLength(DataType::name)) << "Name" << '|' <<
    '|' << setw(Settings::getLength(DataType::year) + Settings::getLength(DataType::month) + Settings::getLength(DataType::day) + 2) << "Date" << '|';
}

ostream& operator << (ostream &outputStream, const Human human){
    cout <<
    '|' << setw(Settings::getLength(DataType::privateID)) << human.privateID << '|' <<
    '|' << setw(Settings::getLength(DataType::name)) << human.name << '|' <<
    '|' << human.birthday << '|';
    return outputStream;
}

istream& operator >> (istream &inputStream, Human &human){
    cout << "Enter name: ";
    human.name = ExceptionEnter::stringData(name);
    cout << "Enter birthday: " << endl;
    cin >> human.birthday;
    
    return inputStream;
}

