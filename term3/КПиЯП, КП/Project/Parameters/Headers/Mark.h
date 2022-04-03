//
//  Mark.h
//  Project
//
//  Created by Andrej Hurynovič on 27.10.20.
//

#ifndef Mark_h
#define Mark_h

#include "ExceptionEnter.h"
#include "Settings.h"

using namespace std;


class Mark {
protected:
    int mark;
    bool resit;
    string subject;
public:
    Mark(int mark = -1, bool resit = false, string subject = "UNDEF"){
        this->mark = mark;
        this->resit = resit;
        this->subject = subject;
    }
    
    int getMark();
    bool getResit();
    string getSubject();
    
    void setMark(int);
    void setResit(bool);
    void setSubject(string);
    
    
    static void printSpreadsheet();
    friend ostream& operator << (ostream &stream, Mark mark);
    friend istream& operator >> (istream &stream, Mark &mark);
    
    ~Mark(){};
};


#endif /* Mark_h */
