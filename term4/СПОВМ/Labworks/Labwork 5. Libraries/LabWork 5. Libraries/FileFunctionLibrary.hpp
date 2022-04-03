//
//  FileFunctionLibrary.hpp
//  FileFunctionLibrary
//
//  Created by Andrej Hurynovič on 5.05.21.
//

#ifndef FileFunctionLibrary_hpp
#define FileFunctionLibrary_hpp

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>


#include <fcntl.h>
#include <signal.h>
#include <filesystem>
#include <sys/stat.h>
#include <aio.h>

#include <pthread.h>

using namespace std;

struct infoStruct {
    int* descriptor;
    long long* size;
    char** bufer;
};

class functions {
public:
    static void* readFromFileToBufer(void* informationPointer);
    static void* writeToFileFromBufer(void* informationPointer);
};

#endif /* FileFunctionLibrary_hpp */
