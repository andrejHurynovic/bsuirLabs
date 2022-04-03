//
//  Bachelor.h
//  Project
//
//  Created by Andrej Hurynovič on 27.10.20.
//

#ifndef Bachelor_h
#define Bachelor_h

#include <vector>
#include "Human.h"
#include "Mark.h"
#include "Benefit.h"

class Bachelor: public Human {
protected:
    string group;
    float scholarship;
    bool showScholarship;
    vector<Mark> marks;
    vector<Benefit> benefits;
    
public:
    Bachelor(string group = "EMPTY ", float scholarship = -1, bool showScholarship = true){
        this->group = group;
        this->scholarship = scholarship;
        this->showScholarship = showScholarship;
    };
    
    void writeToFile(File&);
    void readFromFile(File&);
    
    void calculateScholarship(float base = Settings::getBachelorBase());
    
    string getGroup();
    float getScholarship();
    bool getShowScholarship();
    Mark* getMarkForID(int);
    unsigned long getMarksSize();
    Benefit* getBenefitForID(int);
    unsigned long getBenefitsSize();
    
    void setGroup(string);
    void setScholarship(float);
    void setShowScholarship(bool);
    void addMark(Mark);
    void addBenefit(Benefit);
    
    void removeMarkForID(int);
    void removeBenefitForID(int);
    
    
    
    void editMenu(bool);
    void edit(int);
    
    static void printSpreadsheet(bool);
    void printMarksAndBenefits();
    friend ostream& operator << (ostream &stream, Bachelor bachelor);
    friend istream& operator >> (istream &stream, Bachelor &bachelor);
    
    ~Bachelor(){
        marks.clear();
        benefits.clear();
    };
};

#endif /* Bachelor_h */
