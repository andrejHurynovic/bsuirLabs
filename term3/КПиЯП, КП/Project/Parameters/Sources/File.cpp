//
//  File.cpp
//  Project
//
//  Created by Andrej Hurynovič on 3.01.21.
//

#include "File.h"


FileType File::getType(){
    return type;
}

void File::setType(FileType type){
    this->type = type;
}

bool File::endOfFile(){
    
    long now = file.tellp();
    
    file.seekg(0, ios::end);
    
    long fileLenght = file.tellp();
    
    file.seekg(now, ios::beg);
        
    if(now == fileLenght){
        return true;
    }else{
        return false;
    }
}

