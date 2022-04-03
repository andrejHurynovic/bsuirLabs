//
//  Publication.h
//  Project
//
//  Created by Andrej Hurynovič on 25.11.20.
//

#ifndef Publication_h
#define Publication_h


#include <iostream>
#include "Settings.h"
#include "ExceptionEnter.h"

using namespace std;


class Publication {
protected:
    string name;
    string journalName;
    bool accreditation;
    
public:
    Publication(string name = "UNDEFINED", string journalName = "UNDEFINED", bool accreditation = false){
        this->name = name;
        this->journalName = journalName;
        this->accreditation = accreditation;
    }
    
    string getPublicationName();
    string getJournalName();
    bool getAccreditation();
    
    void setPublicationName(string);
    void setJournalName(string);
    void setAccreditation(bool);
    
    
    
    friend ostream& operator << (ostream &stream, Publication publication);
    friend istream& operator >> (istream &stream, Publication &publication);
    
    ~Publication(){};
};

#endif /* Publication_h */
