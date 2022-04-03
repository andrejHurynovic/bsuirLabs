//
//  main.cpp
//  LabWork 5. Libraries
//
//  Created by Andrej Hurynovič on 5.05.21.
//

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>


#include <fcntl.h>
#include <signal.h>
#include <filesystem>
#include <sys/stat.h>
#include <aio.h>
#include <dlfcn.h>

#include <pthread.h>

#include <malloc/malloc.h>
#include "FileFunctionLibrary.hpp"


using namespace std;


long long getFileSize(const char* fileName) {
    struct stat status;
    stat(fileName, &status);
    return status.st_size;
}


int main() {
    
    void *dynamicLibrary = dlopen("/Users/andrejhurynovic/Library/Developer/Xcode/DerivedData/LabWork_5._Libraries-cnwthqklfteutxdrcowhkznmgvar/Build/Products/Debug/libaioFunctions.dylib", RTLD_GLOBAL);
    
    if(dynamicLibrary) {
        vector<string> vector;
        
        const string writeFilePath = "/users/andrejhurynovic/master.txt";
        const string readFolderPath = "/users/andrejhurynovic/Downloads";
        
        for (const auto & entry : filesystem::directory_iterator(readFolderPath)) {
            string filePath = entry.path();
            if (filePath.compare(filePath.size() - 4, 4, ".txt") == 0) {
                vector.push_back(filePath);
            }
        }
        
        if(vector.empty()){
            cout << "No .txt files in  " << readFolderPath;
        }
        
        
        
        sigset_t firstSignalSet;
        sigemptyset(&firstSignalSet);
        sigaddset(&firstSignalSet, SIGUSR1);
        sigset_t secondSignalSet;
        sigemptyset(&secondSignalSet);
        sigaddset(&secondSignalSet, SIGUSR2);
        
        
        
        int writeFileDiscriptor = open(writeFilePath.c_str(), O_CREAT | O_TRUNC | O_WRONLY);
        int readFileDiscriptor;
        
        char* bufer;
        long long fileSize;
        
        
        
        infoStruct writeStructure;
        writeStructure.bufer = &bufer;
        writeStructure.size = &fileSize;
        writeStructure.descriptor = &writeFileDiscriptor;
        
        infoStruct readerStructure;
        readerStructure.bufer = &bufer;
        readerStructure.size = &fileSize;
        readerStructure.descriptor = &readFileDiscriptor;
        
        pthread_t readerThread;
        pthread_create(&readerThread, NULL, &functions::readFromFileToBufer, &readerStructure);
        
        pthread_t writerThread;
        pthread_create(&writerThread, NULL, &functions::writeToFileFromBufer, &writeStructure);
        
        
        
        while(!vector.empty()) {
            string tempFileName = *vector.rbegin();
            vector.pop_back();
            const char* fileName = tempFileName.c_str();
            readFileDiscriptor = open(fileName,  O_RDONLY);
            fcntl(readFileDiscriptor, F_SETLK);
            
            fileSize = getFileSize(fileName);
            bufer = new char[fileSize];
            
            pthread_kill(readerThread, SIGUSR1);
            sigwait(&secondSignalSet, NULL);
            
            pthread_kill(writerThread, SIGUSR2);
            sigwait(&firstSignalSet, NULL);
            
            
            close(readFileDiscriptor);
            cout << bufer << endl;
            
            delete[] bufer;
        }
        close(writeFileDiscriptor);
        pthread_cancel(writerThread);
        pthread_join(writerThread, NULL);
        pthread_cancel(readerThread);
        pthread_join(readerThread, NULL);
        dlclose(dynamicLibrary);
    } else {
        cout << "Cannot open library!";
    }
}

//extern void Hello();
