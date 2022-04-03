//
//  File.h
//  Password manager
//
//  Created by Andrej Hurynovič on 16.05.21.
//

#ifndef File_Manager_h
#define File_Manager_h

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>

class File {
    int descriptor;
    aiocb aio = {};
    
public:
    File(string path = "data.re") {
        descriptor = open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC);
        
        #warning "Add error check"
        
        aio.aio_fildes = descriptor;
    }
    
    void read(void* source, long long size = 16, long long offset = 0) {
        aio.aio_buf = source;
        aio.aio_offset = offset;
        aio.aio_nbytes = size;
        aio.aio_lio_opcode = LIO_READ;
        
        if (aio_read(&aio) == -1) {
            cout << endl << "Error at aio_read(): " << strerror(errno);
        }
        
        while(aio_error(&aio) == EINPROGRESS);
        aio_return(&aio);
    }

    void write(void* source, long long size = 16, long long offset = 0) {
        aio.aio_buf = source;
        aio.aio_offset = offset;
        aio.aio_nbytes = size;
        aio.aio_lio_opcode = LIO_WRITE;
        
        if (aio_write(&aio) == -1) {
            cout << endl << "Error at aio_write(): " << strerror(errno);
        }
        
        while(aio_error(&aio) == EINPROGRESS);
        aio_return(&aio);
    }
    
    ~File() {
        close(descriptor);
#warning "Add error check"
    }
};

#endif /* File_h */
