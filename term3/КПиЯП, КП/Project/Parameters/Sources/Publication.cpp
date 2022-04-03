//
//  Publication.cpp
//  Project
//
//  Created by Andrej Hurynovič on 13.12.20.
//

#include "Publication.h"


string Publication::getPublicationName(){
    return this->name;
}

string Publication::getJournalName(){
    return this->journalName;
}

bool Publication::getAccreditation(){
    return this->accreditation;
}


void Publication::setPublicationName(string name){
    this->name = name;
}

void Publication::setJournalName(string journalName){
    this->journalName = journalName;
}

void Publication::setAccreditation(bool accreditation){
    this->accreditation = accreditation;
}




ostream& operator << (ostream &outputStream, const Publication publication){
    cout <<
    '|' << setw(Settings::getLength(DataType::name)) << publication.name << '|' <<
    '|' << setw(Settings::getLength(DataType::journalName)) << publication.journalName << '|' <<
    '|' << setw(Settings::getLength(DataType::accreditation)) << publication.accreditation << '|';
    return outputStream;
}

istream& operator >> (istream &inputStream, Publication &publication){
    cout << "Enter publication name: ";
    publication.name = ExceptionEnter::stringData(publicationName);
    cout << "Enter journal name: ";
    publication.journalName = ExceptionEnter::stringData(journalName);
    cout << "Does this journal have accreditation? (0/1): " << endl;
    publication.accreditation = ExceptionEnter::NumberData<int>(accreditation);
    
    return inputStream;
}
