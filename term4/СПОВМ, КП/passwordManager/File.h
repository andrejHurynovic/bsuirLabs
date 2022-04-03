#ifndef FILE_H
#define FILE_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>

#include "Bundle.h"
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QCryptographicHash>

using namespace std;

class File: QObject {
    QString fileName;
    
    int descriptor;
    
    aiocb aio = {};
    
public:
    File() {}
    
    bool newFile();
    bool openFile();
    bool saveFile();
    bool saveFileAs();
    void closeFile();
    
    bool openFileAndGetDescriptor(bool);

    void setFileName(QString);
    QString getFileName();
    
    
    void read(void*, long long size, long long offset);
    void write(void*, long long size, long long offset);
    
    vector<Bundle> readBundles(QString);
    void writeBundles(vector<Bundle>, QString);
    bool validatePassword(QString);
    
    ~File() {
        close(descriptor);
    }
};

#endif // FILE_H
