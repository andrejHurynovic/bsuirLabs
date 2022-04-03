//
//  Human.hpp
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef Human_hpp
#define Human_hpp

#include <iostream>
#include <iomanip>
#include "Date.hpp"

using namespace std;

class Human{
protected:
    string surname;
    string name;
    Date birhtday;
    
public:
    Human(string surname = "NULL", string name = "NULL", Date birhtday = Date()){
        this->surname = surname;
        this->name = name;
        this->birhtday = birhtday;
    }
    
    void setSurname(string surname);
    void setName(string name);
    void setDate(Date birhtday);
    
    string getSurname();
    string getName();
    Date getDate();
    
    void printSpreadsheet();
    
    friend ostream& operator << (ostream &outputStream, const Human human);
    friend istream& operator >> (istream &inputStream, Human &human);
    
    ~Human(){};
};

#endif /* Human_hpp */
