//
//  String.cpp
//  LabWork 3. String
//
//  Created by Андрэй Гурыновіч on 20.09.20.
//

#include "StringObject.h"



StringObject StringObject::operator = (const StringObject &additionalString){
    
    if(&additionalString != this){
        
        delete [] this->string;
        
        this->length = additionalString.length;
        this->string = new char[length + 1];
        this->string[length] = '\0';
        
        
        strcpy(this->string, additionalString.string);
    }
    return *this;
}

StringObject StringObject::operator + (const StringObject &additionalString){
    StringObject newString(this->length + additionalString.length);
    
    for(int i = 0; i < this->length; i++){
        newString.string[i] = this->string[i];
    }
    
    for(unsigned long i = this->length; i < this->length + additionalString.length; i++){
        newString.string[i] = additionalString.string[i - this->length];
    }
    
    return newString;
    
}

StringObject StringObject::operator + (const std::string &additionalString){
    StringObject newString(this->length + additionalString.length());
    
    for(int i = 0; i < this->length; i++){
        newString.string[i] = this->string[i];
    }
    
    for(unsigned long i = this->length; i < this->length + additionalString.length(); i++){
        newString.string[i] = additionalString[i - this->length];
    }
    
    return newString;
    
}

StringObject operator + (const std::string &string, const StringObject &additionalString){
    StringObject newString(string.length() + additionalString.length);
    
    for(unsigned long i = 0; i < string.length(); i++){
        newString.string[i] = string[i];
    }
    
    for(unsigned long i = string.length(); i < string.length() + additionalString.length; i++){
        newString.string[i] = additionalString.string[i - string.length()];
    }
    
    return newString;
    
}

StringObject StringObject::operator + (const char &additionalChar){
    StringObject newString(this->length + 1);
    
    for(int i = 0; i < this->length; i++){
        newString.string[i] = this->string[i];
    }
    
    newString.string[newString.length - 1] = additionalChar;
    
    return newString;
    
}

StringObject operator + (char additionalChar, const StringObject& string){
    StringObject newString(string.length + 1);
    
    newString[0] = additionalChar;
    
    for(int i = 1; i < newString.length; i++){
        newString.string[i] = string.string[i - 1];
    }
    
    return newString;
    
}

void StringObject::operator += (const StringObject &additionalString){
    *this = *this + additionalString;
}

void StringObject::operator += (const std::string &additionalString){
    char* tempString = new char[this->length + additionalString.length() + 1];
    tempString[this->length + additionalString.length()] = '\0';
    
    for(int i = 0; i < this->length; i++){
        tempString[i] = this->string[i];
    }
    
    for(unsigned long i = this->length; i < this->length + additionalString.length(); i++){
        tempString[i] = additionalString[i - this->length];
    }
    
    delete [] this->string;
    
    this->length = this->length + additionalString.length();
    this->string = tempString;
}

void StringObject::operator += (char* &additionalString){
    char* tempString = new char[this->length + strlen(additionalString) + 1];
    tempString[this->length + strlen(additionalString)] = '\0';
    
    for(int i = 0; i < this->length; i++){
        tempString[i] = this->string[i];
    }
    
    for(unsigned long i = this->length; i < this->length + strlen(additionalString); i++){
        tempString[i] = additionalString[i - this->length];
    }
    
    delete [] this->string;
    
    this->length = this->length + strlen(additionalString);
    this->string = tempString;
}


void StringObject::operator += (const char &additionalChar){
    char* tempString = new char[this->length + 2];
    tempString[this->length + 1] = '\0';
    
    for(int i = 0; i < this->length; i++){
        tempString[i] = this->string[i];
    }
    
    tempString[length] = additionalChar;
    
    delete [] this->string;
    
    this->length++;
    this->string = tempString;
}

bool StringObject::operator == (const StringObject &additionalString){
    
    for(int i = 0; i < this->length; i++){
        if(this->string[i] != additionalString.string[i]){
            return 0;
        }
    }
    return 1;
}
//    bool operator == (const StringObject &additionalString){
//        if(&additionalString == this){
//            return 1;
//        }
//
//        if(this->length != additionalString.length){
//            return 0;
//        }
//
//        for(int i = 0; i < this->length; i++){
//            if(this->string[i] != additionalString.string[i]){
//                return 0;
//            }
//        }
//        return 1;
//    }

bool StringObject::operator != (const StringObject &additionalString){
    if(*this == additionalString){
        return 0;
    }else{
        return 1;
    }
}

bool StringObject:: operator > (const StringObject &additionalString){
    return this->length > additionalString.length;
}

bool StringObject:: operator < (const StringObject &additionalString){
    return this->length < additionalString.length;
}

bool StringObject:: operator >= (const StringObject &additionalString){
    return this->length >= additionalString.length;
}

bool StringObject:: operator <= (const StringObject &additionalString){
    return this->length <= additionalString.length;
}

ostream& operator << (ostream& outputStream, const StringObject& string){
    cout << string.string << endl;
    return outputStream;
};

istream& operator >> (istream& inputStream, StringObject& stringObject){
    
    char* string = new char[81];
    cin.getline(string, 81);
    stringObject = StringObject(string);
    
    return inputStream;
}



StringObject StringObject::operator ()(int firstPoint , int secondPoint){
    if(firstPoint > secondPoint){
        return StringObject("Error");
    }
    
    if(this->length < secondPoint){
        return StringObject("Error");
    }
    
    StringObject string(secondPoint - firstPoint + 2);
    string.length = secondPoint - firstPoint + 1;
    string.string[secondPoint - firstPoint + 1] = '\0';
    
    for(int i = firstPoint; i <= secondPoint; i++){
        string.string[i - firstPoint] = this->string[i];
    }
    
    return string;
}

char& StringObject::operator [](int i){
    return this->string[i];
}

