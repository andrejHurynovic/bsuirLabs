//
//  Algorithms.cpp
//  Project
//
//  Created by Andrej Hurynovič on 10.01.21.
//

#include "Algorithms.h"

void Algorithms::writeBachelorToFile(Bachelor& bachelor, File& file){
    bachelor.Human::writeToFile(file);
    
    file.write(bachelor.getGroup());
    file.write(bachelor.getScholarship());
    
    unsigned long marksSize = bachelor.getMarksSize();
    file.write(marksSize);
    
    for(int i = 0; i < marksSize; i++){
        file.write(*bachelor.getMarkForID(i));
    }
    
    unsigned long benefitsSize = bachelor.getBenefitsSize();
    file.write(benefitsSize);
    
    for(int i = 0; i < benefitsSize; i++){
        file.write(*bachelor.getBenefitForID(i));
    }
}

fstream Algorithms::openFile(enum FileType type, bool write){
    string fileName;
    
    switch (type) {
        case bachelors:
            fileName = "Bachelors";
            break;
        case masters:
            fileName = "Masters";
            break;
        case doctors:
            fileName = "Doctors";
            break;
        case settings:
            fileName = "Settings";
            break;
    }
    
    fstream file;
    
    if(write){
        file.open(fileName, ios::trunc | ios::binary | ios::out);
    }else{
        file.open(fileName, ios::binary | ios::in);
    }
    
    if(!file.is_open()){
        ofstream tempFile(fileName, ios::binary);
        
        tempFile.close();
        
        if(type == settings){
            Settings::setTheDefaultSettings();
        }
        
        file.open(fileName, ios::binary | ios::in);
        return file;
    }
    
    return file;
}

float Algorithms::calclulateBachelorScholarship(Bachelor& bachelor, float base){
    
    float scholarship = base;
    
    if(Settings::getMarks()){
        float marksModifier = 0;
        for (int i = 0; i < bachelor.getMarksSize(); i++){
            marksModifier += bachelor.getMarkForID(i)->getMark();
        }
        marksModifier /= bachelor.getMarksSize();
        if(marksModifier >= 7){
            if(marksModifier >= 7 && marksModifier < 8){
                marksModifier = Settings::getMarkFirst();
            }
            if(marksModifier >= 8 && marksModifier < 9){
                marksModifier = Settings::getMarkSecond();
            }
            if(marksModifier >= 9 && marksModifier <= 10){
                marksModifier = Settings::getMarkThird();
            }
            scholarship += ((base * marksModifier) - base);
        }
    }
    
    if(Settings::getResit()){
        for (int i = 0; i < bachelor.getMarksSize(); i++){
            if(bachelor.getMarkForID(i)->getResit()){
                scholarship = 0;
                return scholarship;
            }
        }
    }
    
    if(Settings::getBenefits()){
        for(int i = 0; i < bachelor.getBenefitsSize(); i++){
            scholarship += base * bachelor.getBenefitForID(i)->getModifier() - base;
        }
    }
    return scholarship;

}

