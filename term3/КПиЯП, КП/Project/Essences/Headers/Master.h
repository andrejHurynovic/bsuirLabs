//
//  Master.h
//  Project
//
//  Created by Andrej Hurynovič on 10.11.20.
//

#ifndef Master_h
#define Master_h

#include "Bachelor.h"
#include "Publication.h"

class Master: public Bachelor {
protected: 
    Publication* publication;
public:
    Master(Publication* publication = NULL){
        this->publication = publication;
    };
    
    Master(const Master& master){
        this->privateID = master.privateID;
        this->name = master.name;
        this->birthday = master.birthday;

        this->group = master.group;
        this->scholarship = master.scholarship;
        this->showScholarship = master.showScholarship;
        this->marks = master.marks;
        this->benefits = master.benefits;
        
        if(master.publication){
            publication = new Publication (*master.publication);
        }else{
            publication = NULL;
        }
        
        
    }
    
    void writeToFile(File&);
    void readFromFile(File&);
    
    void calculateScholarship(float base = Settings::getMasterBase());
    
    Publication* getPublication();
    
    void setPublication(Publication*);
    
    void editMenu(bool);
    void edit(int key);
    
    static void printSpreadsheet(bool);
    friend ostream& operator << (ostream &stream, Master master);
    friend istream& operator >> (istream &stream, Master &master);
    
    ~Master(){
//        delete publication;
    };
};

#endif /* Master_h */
