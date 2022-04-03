//
//  File.h
//  Project
//
//  Created by Andrej Hurynovič on 3.01.21.
//

#ifndef File_h
#define File_h

#include <iostream>
#include "ExceptionFile.h"

class File {
private:
    fstream file;
    FileType type;
    
public:
    File(FileType type, bool write){
        this->type = type;
        if(write){
            this->file = ExceptionFile::openFile(type, true);
        }else{
            this->file = ExceptionFile::openFile(type, false);
        }
    }
    
    template <typename dataType>
    void read(dataType *data){
        file.read((char*)data, sizeof(*(data)));
    }
    
    template <typename dataType>
    void write(dataType data){
        file.write((char*)&data, sizeof(dataType));
    }
   
        
    FileType getType();
    
    void setType(FileType);
    
    bool endOfFile();
    
    ~File(){
        file.close();
    }
};

#endif /* File_h */
