#include "Bundle.h"


void Bundle::setName(char* string) {
    strlcpy(name, string, sizeof(name));
}
void Bundle::setUsername(char* string) {
    strlcpy(username, string, sizeof(username));
}
void Bundle::setPassword(char* string) {
    strlcpy(password, string, sizeof(password));
}



char* Bundle::getName() {
    return name;
}
char* Bundle::getUsername() {
    return username;
}
char* Bundle::getPassword() {
    return password;
}



void Bundle::encrypt(enum KeyLenght keyLenght, unsigned char* passwordHash){
    AES aes(keyLenght);
    unsigned int outputSize;
    unsigned char* tempString = aes.EncryptECB((unsigned char*)name, sizeof(name), passwordHash, outputSize);
    strlcpy(name, (char*)tempString, sizeof(name));
    tempString = aes.EncryptECB((unsigned char*)username, sizeof(username), passwordHash, outputSize);
    strlcpy(username, (char*)tempString, sizeof(username));
    tempString = aes.EncryptECB((unsigned char*)this->password, sizeof(this->password), passwordHash, outputSize);
    strlcpy(this->password, (char*)tempString, sizeof(this->password));
}

void Bundle::decrypt(enum KeyLenght keyLenght, unsigned char* passwordHash){
    AES aes(keyLenght);
    
    unsigned char* tempString = aes.DecryptECB((unsigned char*)name, sizeof(name), passwordHash);
    strlcpy(name, (char*)tempString, sizeof(name));
    tempString = aes.DecryptECB((unsigned char*)username, sizeof(username), passwordHash);
    strlcpy(username, (char*)tempString, sizeof(username));
    tempString = aes.DecryptECB((unsigned char*)this->password, sizeof(this->password), passwordHash);
    strlcpy(this->password, (char*)tempString, sizeof(this->password));
}
