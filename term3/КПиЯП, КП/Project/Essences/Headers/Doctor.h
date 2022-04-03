//
//  Doctor.h
//  Project
//
//  Created by Andrej Hurynovič on 10.11.20.
//

#ifndef Doctor_h
#define Doctor_h

#include"Master.h"

class Doctor: public Master{
protected:
    bool dissertationComplited;
public:
    Doctor(){
        dissertationComplited = false;
    };
    
    void writeToFile(File&);
    void readFromFile(File&);
    
    void calculateScholarship(float base = Settings::getDoctorBase());
    
    bool getDissertationComplited();
    
    void setDissertationComplited(bool);
    
    void editMenu(bool);
    void edit(int key);
    
    static void printSpreadsheet(bool);
    friend ostream& operator << (ostream &stream, Doctor doctor);
    friend istream& operator >> (istream &stream, Doctor &doctor);
    
    ~Doctor(){};
};

#endif /* Doctor_h */
