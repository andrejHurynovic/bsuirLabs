//
//  BorderCrossing.h
//  LabWork 5. Inheritance
//
//  Created by Андрэй Гурыновіч on 7.10.20.
//

#ifndef BorderCrossing_h
#define BorderCrossing_h

#include "Date.hpp"


struct BorderCrossing {
    BorderCrossing(string country = "NULL", Date date = Date(0, 0, 0)){
        this-> country = country;
        this-> date = date;
    }
    
    string country;
    Date date;
};

#endif /* BorderCrossing_h */
