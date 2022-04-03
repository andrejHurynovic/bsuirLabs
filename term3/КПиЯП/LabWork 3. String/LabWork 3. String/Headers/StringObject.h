//
//  StringObject.h
//  LabWork 3. String
//
//  Created by Андрэй Гурыновіч on 22.09.20.
//

#ifndef StringObject_h
#define StringObject_h

#include <iostream>
#include <string>

using namespace std;

class StringObject{
    
private:
    char* string;
    unsigned long length;
    
public:
    StringObject(unsigned long lenght = 1){
        this->length = lenght;
        this->string = new char[lenght + 1];
        this->string[lenght] = '\0';
    }
    
    explicit StringObject(char* const &string){
        this->length = strlen(string);
        this->string = new char[length + 1];
        this->string[length] = '\0';
        
        for(int i = 0; i < length; i++){
            this->string[i] = string[i];
        }
    }
    
    explicit StringObject(std::string const &string){
        this->length = string.length();
        this->string = new char[length + 1];
        this->string[length] = '\0';
        
        for(int i = 0; i < length; i++){
            this->string[i] = string[i];
        }
    }
    
    StringObject(StringObject const &additionalString){
        this->length = additionalString.length;
        this->string = new char[length + 1];
        this->string[length] = '\0';
        
        for(int i = 0; i < length; i++){
            this->string[i] = additionalString.string[i];
        }
    }
    
    StringObject operator = (const StringObject &additionalString);
    
    StringObject operator + (const StringObject &additionalString);
    StringObject operator + (const std::string &additionalString);
    friend StringObject operator + (const std::string &string, const StringObject &additionalString);
    StringObject operator + (const char &additionalChar);
    friend StringObject operator + (char additionalChar, const StringObject& string);
    
    void operator += (const StringObject &additionalString);
    void operator += (const std::string &additionalString);
    void operator += (char* &additionalString);
    void operator += (const char &additionalChar);
    
    bool operator == (const StringObject &additionalString);
    
    bool operator != (const StringObject &additionalString);
    
    bool operator > (const StringObject &additionalString);
    
    bool operator < (const StringObject &additionalString);
    
    bool operator >= (const StringObject &additionalString);
    
    bool operator <= (const StringObject &additionalString);
    
    friend ostream& operator << (ostream& outputStream, const StringObject& string);
    friend istream& operator >> (istream& inputStream, StringObject& stringObject);
    
    StringObject operator ()(int firstPoint , int secondPoint);
    
    char& operator [](int i);
    
    ~StringObject(){
        delete [] string;
    }
    
};


#endif /* StringObject_h */
