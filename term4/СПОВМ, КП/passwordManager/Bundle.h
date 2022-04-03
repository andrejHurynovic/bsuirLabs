#ifndef Bundle_h
#define Bundle_h

#include <iostream>
#include <QDebug>
#include <QString>

#include "AES.h"
#include "Settings.h"

using namespace std;

class Bundle {
    char name[128] = {};
    char username[128] = {};
    char password[128] = {};
    
public:
    Bundle(string name = string(""), string username = string(""), string password = string("")) {
        strlcpy(this->name, name.c_str(), sizeof(name));
        strlcpy(this->username, username.c_str(), sizeof(username));
        strlcpy(this->password, password.c_str(), sizeof(password));
    };
    
    void setName(char*);
    void setUsername(char*);
    void setPassword(char*);
    
    char* getName();
    char* getUsername();
    char* getPassword();
    
    void encrypt(enum KeyLenght , unsigned char*);
    void decrypt(enum KeyLenght , unsigned char*);
    
    
    ~Bundle(){};
};

#endif /* Bundle_h */
