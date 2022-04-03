//
//  Exception File.cpp
//  Project
//
//  Created by Andrej Hurynovič on 17.12.20.
//

#include "ExceptionFile.h"
#include "Settings.h"
#include "Algorithms.h"



fstream ExceptionFile::openFile(enum FileType type, bool write){
    return Algorithms::openFile(type, write);
}
