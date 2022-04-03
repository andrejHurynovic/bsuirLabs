//
//  Date.cpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#include "Date.hpp"
#include <iomanip>

#include "ExceptionEnter.hpp"

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
    date.day = ExceptionEnter::EnterIntWithCheck(day, 1, 31); 
    cout << "Month: ";
    date.month = ExceptionEnter::EnterIntWithCheck(month, 1, 12);
    cout << "Year: ";
    date.year = ExceptionEnter::EnterIntWithCheck(year, -9999, 2020);

    return inputStream;
}

