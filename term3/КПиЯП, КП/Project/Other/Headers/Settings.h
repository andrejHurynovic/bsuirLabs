//
//  Settings.h
//  Project
//
//  Created by Andrej Hurynovič on 13.12.20.
//

#ifndef Settings_h
#define Settings_h

#include "Benefit.h"
#include "File.h"

class Settings{
    
protected:
    static float bachelorBase;
    static float masterBase;
    static float doctorBase;
    
    static bool benefits;
    static float disabledBenefit;
    static float socialBenefit;
    static float councilBenefit;
    static float personalBenefit;
    
    static bool marks;
    static float markFirst;
    static float markSecond;
    static float markThird;
    
    static bool resit;
    
    static bool publication;
    static bool journalAccreditation;
    
    static bool dissertationComplited;
    
public:
    static void getSettingsFromFile();
    static void setSettingsToFile();
    static void setTheDefaultSettings();
    
    static void menu();
    static void editSettings();
    static void printSettings();
    
    static int getLength(enum DataType);
    
    static float getBachelorBase();
    static float getMasterBase();
    static float getDoctorBase();
    
    static bool getBenefits();
    static float getBenefitByType(enum BenefitType);
    
    static bool getMarks();
    static float getMarkFirst();
    static float getMarkSecond();
    static float getMarkThird();
    
    static bool getResit();
    
    static bool getPublication();
    static bool getJournalAccreditation();
    
    static bool getDissertationComplited();
    
};


#endif /* Settings_h */
