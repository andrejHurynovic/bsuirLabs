//
//  Human.h
//  Project
//
//  Created by Andrej Hurynovič on 27.10.20.
//

#ifndef Human_h
#define Human_h

#include <iostream>
#include "iomanip"
#include "Settings.h"
#include "Date.h"
#include "ExceptionEnter.h"


using namespace std;

class Human {
protected:
    string privateID;
    string name;
    Date birthday;
public:
    Human(string privateID = "UNDEFINE", string name = "UNDEFINED", Date birthday = Date()){
        this->privateID = privateID;
        this->name = name;
        this->birthday = birthday;
    }
    
    void writeToFile(File&);
    void readFromFile(File&);
    
    string getPrivateID();
    string getName();
    Date getBirthday();
    
    void setPrivateID(string);
    void setName(string);
    void setBirthday(Date);
    
    void editMenu(bool);
    void edit(int);
    
    static void printSpreadsheet();
    friend ostream& operator << (ostream &stream, Human human);
    friend istream& operator >> (istream &stream, Human &human);
    
    ~Human(){};
};

#endif /* Human_h */
