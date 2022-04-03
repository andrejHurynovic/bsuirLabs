//
//  Date.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Date.hpp"
#include <iomanip>

Date Date::operator = (const Date& otherDate){
    
    if(&otherDate != this){
    this->day = otherDate.day;
    this->month = otherDate.month;
    this->year = otherDate.year;
    }
    return *this;
}

ostream& operator << (ostream &outputStream, const Date date){
    cout << "||" << setw(2) << date.day << "." << setw(2) << date.month << "." << setw(4) << date.year <<'|';
    return outputStream;
}
istream& operator >> (istream &inputStream, Date &date){
    
    cout << "Day: ";
    cin >> date.day;
    cout << "Month: ";
    cin >> date.month;
    cout << "Year: ";
    cin >> date.year;
    
    return inputStream;
}

