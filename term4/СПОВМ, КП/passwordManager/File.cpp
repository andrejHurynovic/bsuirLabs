#include "File.h"

bool File::newFile() {
    fileName = QFileDialog::getSaveFileName(NULL, tr("Create new file"), "/", tr("Password Manager Data (*.pmd)"));
    if(!fileName.size()){
        return false;
    }
    openFileAndGetDescriptor(true);
    return true;
}

bool File::openFile() {
    fileName = QFileDialog::getOpenFileName(NULL, tr("Open file"), "/", tr("Password Manager Data (*.pmd)"));
    if(!fileName.size()){
        return false;
    }
    return openFileAndGetDescriptor(false);
}

bool File::saveFile() {
    return openFileAndGetDescriptor(true);
}

bool File::saveFileAs() {
    fileName = QFileDialog::getSaveFileName(NULL, tr("Choose or creare file"), "/", tr("Password Manager Data (*.pmd)"));
    if(!fileName.size()){
        return false;
    }
    return openFileAndGetDescriptor(true);
}

void File::closeFile() {
    if(!close(descriptor)) {
        qDebug() << "Error at close: " << strerror(errno);
    }
}



bool File::openFileAndGetDescriptor(bool clear) {
    if(clear){
        descriptor = open(fileName.toStdString().c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IROTH | S_IRWXG | S_IRWXU);
    } else {
        descriptor = open(fileName.toStdString().c_str(), O_RDWR | O_CREAT, S_IROTH | S_IRWXG | S_IRWXU);
    }
    
    aio.aio_fildes = descriptor;
    
    if(!descriptor) {
        qDebug() << "Error at open: " << strerror(errno);
        return false;
    } else {
        return true;
    }
}




void File::setFileName(QString fileName){
    this->fileName = fileName;
}

QString File::getFileName(){
    return fileName;
}



void File::read(void* source, long long size = 16, long long offset = 0) {
    aio.aio_buf = source;
    aio.aio_offset = offset;
    aio.aio_nbytes = size;
    aio.aio_lio_opcode = LIO_READ;
    
    if (aio_read(&aio) == -1) {
        qDebug() << "Error at aio_read(): " << strerror(errno);
    }
    
    while(aio_error(&aio) == EINPROGRESS);
    aio_return(&aio);
}

void File::write(void* source, long long size = 16, long long offset = 0) {
    aio.aio_buf = source;
    aio.aio_offset = offset;
    aio.aio_nbytes = size;
    aio.aio_lio_opcode = LIO_WRITE;
    
    if (aio_write(&aio) == -1) {
        qDebug()  << "Error at aio_write(): " << strerror(errno);
    }
    
    while(aio_error(&aio) == EINPROGRESS);
    aio_return(&aio);
}



vector<Bundle> File::readBundles(QString password){
    vector<Bundle> bundles;
    enum KeyLenght keyLenght;
    unsigned char* passwordHash;
    
    read(&keyLenght, sizeof(KeyLenght), 0);
    
    switch (keyLenght) {
        case bits128:{
            QCryptographicHash qch(QCryptographicHash::Md4);
            qch.addData(QByteArray(password.toStdString().c_str()));
            
            passwordHash = new unsigned char[16]();
            
            memcpy(passwordHash, qch.result(), 16);
            break;
        }
        case bits192: {
            QCryptographicHash qch(QCryptographicHash::Sha256);
            qch.addData(QByteArray(password.toStdString().c_str()));
            
            passwordHash = new unsigned char[24]();
            
            memcpy(passwordHash, qch.result(), 24);
            break;
        }
        case bits256: {
            QCryptographicHash qch(QCryptographicHash::Sha256);
            qch.addData(QByteArray(password.toStdString().c_str()));
            
            passwordHash = new unsigned char[32]();
            
            memcpy(passwordHash, qch.result(), 32);
            break;
        }
    }
    
    int rows = 0;
    read(&rows, sizeof(int), sizeof(KeyLenght) + sizeof(Bundle));
    
    int offset = sizeof(KeyLenght) + sizeof(int) + sizeof(Bundle);
    
    for (int i = 0; i < rows; i++) {
        Bundle* bundle = new Bundle();
        read(bundle, sizeof(Bundle), offset + sizeof(Bundle) * i);
        bundle->decrypt(keyLenght, passwordHash);
        bundles.push_back(*bundle);
    }
    
    return bundles;
}

void File::writeBundles(vector<Bundle> bundles, QString password) {
    enum KeyLenght keyLenght = Settings::getKeySize();
    unsigned char* passwordHash;
    
    switch (keyLenght) {
        case bits128:{
            QCryptographicHash qch(QCryptographicHash::Md4);
            qch.addData(QByteArray(password.toStdString().c_str()));
            
            passwordHash = new unsigned char[16]();
            
            memcpy(passwordHash, qch.result(), 16);
            break;
        }
        case bits192: {
            QCryptographicHash qch(QCryptographicHash::Sha256);
            qch.addData(QByteArray(password.toStdString().c_str()));
            
            passwordHash = new unsigned char[24]();
            
            memcpy(passwordHash, qch.result(), 24);
            break;
        }
        case bits256: {
            QCryptographicHash qch(QCryptographicHash::Sha256);
            qch.addData(QByteArray(password.toStdString().c_str()));
            
            passwordHash = new unsigned char[32]();
            
            memcpy(passwordHash, qch.result(), 32);
            break;
        }
    }
    

    write(&keyLenght, sizeof(KeyLenght), 0);

    Bundle testBundle;
    testBundle.encrypt(keyLenght, passwordHash);
    write(&testBundle, sizeof(Bundle), sizeof(KeyLenght));


    int rows = bundles.size();
    write(&rows, sizeof(int), sizeof(KeyLenght) + sizeof(Bundle));
    
    int offset = sizeof(KeyLenght) + sizeof(int) + sizeof(Bundle);
    
    for (int i = 0; i < rows; i++) {
        bundles[i].encrypt(keyLenght, passwordHash);
        write(&bundles[i], sizeof(Bundle), offset + i * sizeof(Bundle));
    }
}

bool File::validatePassword(QString password){
    unsigned char* passwordHash;
    KeyLenght keyLenght;
    read(&keyLenght, sizeof(KeyLenght), 0);

    switch (keyLenght) {
        case bits128:{
            QCryptographicHash qch(QCryptographicHash::Md4);
            qch.addData(QByteArray(password.toStdString().c_str()));

            passwordHash = new unsigned char[16]();

            memcpy(passwordHash, qch.result(), 16);
            break;
        }
        case bits192: {
            QCryptographicHash qch(QCryptographicHash::Sha256);
            qch.addData(QByteArray(password.toStdString().c_str()));

            passwordHash = new unsigned char[24]();

            memcpy(passwordHash, qch.result(), 24);
            break;
        }
        case bits256: {
            QCryptographicHash qch(QCryptographicHash::Sha256);
            qch.addData(QByteArray(password.toStdString().c_str()));

            passwordHash = new unsigned char[32]();

            memcpy(passwordHash, qch.result(), 32);
            break;
        }
    }

    Bundle testBundle;
    read(&testBundle, sizeof(Bundle), sizeof(KeyLenght));
    testBundle.decrypt(keyLenght, passwordHash);

    Bundle tempBundle;

    if(strcmp(testBundle.getName(),  tempBundle.getName()) == 0) {
        return true;
    } else {
        return false;
    }
}

