//
//  Date.hpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef Date_hpp
#define Date_hpp

#include <iostream>

using namespace std;

class Date{
private:
    int day;
    int month;
    int year;
public:
    Date(int day = 0, int month = 0, int year = 0){
        this->day = day;
        this->month = month;
        this->year = year;
    }
    
    Date operator = (const Date&);
    
    friend ostream& operator << (ostream &outputStream, const Date date);
    friend istream& operator >> (istream &inputStream, Date &Date);

    ~Date(){};
};

#endif /* Date_hpp */
