//
//  ExceptionFile.h
//  Project
//
//  Created by Andrej Hurynovič on 17.12.20.
//

#ifndef ExceptionFile_h
#define ExceptionFile_h

#include "ExceptionTypes.h"
#include <fstream>

enum FileType{
    bachelors,
    masters,
    doctors,
    settings,
};

class ExceptionFile: public ExceptionTypes{
    public:
    static fstream openFile(enum FileType, bool);
};

#endif /* ExceptionFile_h */
