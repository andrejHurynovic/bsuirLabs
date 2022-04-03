//
//  Mark.cpp
//  Project
//
//  Created by Andrej Hurynovič on 13.12.20.
//

#include "Mark.h"


int Mark::getMark(){
    return this->mark;
}

bool Mark::getResit(){
    return this->resit;
}

string Mark::getSubject(){
    return this->subject;
}

void Mark::setMark(int mark){
    this->mark = mark;
}

void Mark::setResit(bool resit){
    this->resit = resit;
}

void Mark::setSubject(string subject){
    this->subject = subject;
}


void Mark::printSpreadsheet(){
    cout <<
    '|' << setw(Settings::getLength(DataType::subject)) << "Subject" << '|' <<
    '|' << setw(Settings::getLength(DataType::mark)) << "Mark" << '|' <<
    '|' << setw(Settings::getLength(DataType::resit)) << "Resit" << '|';
}


ostream& operator << (ostream &stream, Mark mark){
    cout <<
    setw(Settings::getLength(DataType::subject)) << mark.subject << '|' <<
    '|' << setw(Settings::getLength(DataType::mark)) << mark.mark << '|' <<
    '|' << setw(Settings::getLength(DataType::resit)) << mark.resit << '|';
    ;
    return stream;
}

istream& operator >> (istream &stream, Mark &mark){
    cout << "Enter subject: ";
    mark.subject = ExceptionEnter::stringData(subject);
    cout << "Enter mark: ";
    mark.mark = ExceptionEnter::NumberData<int>(DataType::mark);
    cout << "Did this student resit this subject? (0/1):" << endl;
    mark.resit = ExceptionEnter::NumberData<int>(resit);
    
    return stream;
}
