//
//  Human.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Human.hpp"


void Human::setSurname(string surname){
    this->surname = surname;
}
void Human::setName(string name){
    this->name = name;
}
void Human::setDate(Date birhtday){
    this->birhtday = birhtday;
}
string Human::getSurname(){
    return this->surname;
}
string Human::getName(){
    return this->name;
}
Date Human::getDate(){
    return this->birhtday;
}

void Human::printSpreadsheet(){
    cout << setw(13) << "|  Surname  |" << setw(12) << "|   Name   |" << setw(10) << "| Birthday |"<< endl;
}

ostream& operator << (ostream &outputStream, const Human human){
    cout << '|' << setw(11) << human.surname << "||" << setw(10) << human.name << human.birhtday;
    return outputStream;
}
istream& operator >> (istream &inputStream, Human &human){
    cout << "Enter name(max 10 symbols): ";
    human.name = ExceptionEnter::EnterStringWithCheck(name, 10);
    cout << "Enter surname(max 11 symbols): ";
    human.surname = ExceptionEnter::EnterStringWithCheck(surname, 11);
    cout << "Enter birthday: " << endl;
    cin >> human.birhtday;

    return inputStream;
}
