//
//  Date.cpp
//  LabWork 5. Inheritance
//
//  Created by Andrej Hurynovič on 7.10.20.
//

#include "Date.h"
#include "ExceptionEnter.h"
#include "Settings.h"


Date Date::operator = (const Date& otherDate){
    
    if(&otherDate != this){
        this->day = otherDate.day;
        this->month = otherDate.month;
        this->year = otherDate.year;
    }
    return *this;
}

ostream& operator << (ostream &outputStream, const Date date){
    
    
    cout << setw(Settings::getLength(day)) << date.day <<
    "." << setw(Settings::getLength(month)) << date.month <<
    "." << setw(Settings::getLength(year)) << date.year;
    
    return outputStream;
}

istream& operator >> (istream &inputStream, Date &date){
    
    cout << "Enter day: ";
    date.day = ExceptionEnter::NumberData<int>(day);
    
    cout << "Enter month: ";
    date.month = ExceptionEnter::NumberData<int>(month);
    
    do{
        if(date.month % 2 == 0 && date.day == 31){
            cout << "Less than 31 days this month." << endl;
            cout << "Enter day: ";
            date.day = ExceptionEnter::NumberData<int>(day);
        }else{
            break;
        }
    }while(true);
    
    do{
        if(date.month == 2 && date.day > 29){
            cout << "Less than 30 days this month." << endl;
            cout << "Enter day: ";
            date.day = ExceptionEnter::NumberData<int>(day);
        }else{
            break;
        }
    }while(true);
    
    cout << "Enter year: ";
    date.year = ExceptionEnter::NumberData<int>(year);
    do{
        if(!((date.year % 4 == 0) && !((date.year % 100 == 0) && (date.year % 400 != 0)))){
            if(date.day > 28){
                cout << "This is  a non-leap year, there are less than 29 days in February." << endl;
                cout << "Enter day: ";
                date.day = ExceptionEnter::NumberData<int>(day);
            }else{
                break;
            }
        }else{
            break;
        }
    }while(true);
    
    return inputStream;
}

