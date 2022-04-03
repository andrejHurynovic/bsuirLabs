//
//  FileFunctionLibrary.cpp
//  FileFunctionLibrary
//
//  Created by Andrej Hurynovič on 5.05.21.
//

#include "FileFunctionLibrary.hpp"

void* functions::readFromFileToBufer(void *informationPointer) {
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    
    while(true) {
        sigwait(&set, NULL);
        infoStruct *structure;
        structure = (infoStruct*)informationPointer;
        aiocb aioStructure;
        aioStructure.aio_fildes = *structure->descriptor;
        aioStructure.aio_offset = 0;
        aioStructure.aio_nbytes = *structure->size;
        aioStructure.aio_buf = *structure->bufer;
        aioStructure.aio_lio_opcode = LIO_READ;
        
        if (aio_read(&aioStructure) == -1) {
            cout << endl << "Error at aio_read(): " << strerror(errno);
        }
        
        while(aio_error(&aioStructure) == EINPROGRESS);
        aio_return(&aioStructure);
        usleep(1000);
        kill(getpid(), SIGUSR2);
    }
    return NULL;
}

void* functions::writeToFileFromBufer(void *informationPointer) {
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    
    while(true){
        sigwait(&set, NULL);
        infoStruct *structure;
        structure = (infoStruct*)informationPointer;
        aiocb aioStructure;
        aioStructure.aio_fildes = *structure->descriptor;
        aioStructure.aio_offset = lseek(*structure->descriptor, 0, SEEK_END);
        aioStructure.aio_nbytes = *structure->size;
        aioStructure.aio_buf = *structure->bufer;
        aioStructure.aio_lio_opcode = LIO_WRITE;
        
        if (aio_write(&aioStructure) == -1) {
            cout << endl <<  "Error at aio_write(): " << strerror(errno);
        }
        
        while(aio_error(&aioStructure) == EINPROGRESS);
        aio_return(&aioStructure);
        usleep(1000);
        kill(getpid(), SIGUSR1);
    }
    return NULL;
}
