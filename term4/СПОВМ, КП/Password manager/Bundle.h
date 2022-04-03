//
//  Bundle.h
//  Password manager
//
//  Created by Andrej Hurynovič on 15.05.21.
//

#ifndef Bundle_h
#define Bundle_h

#include <iostream>
#include <uuid/uuid.h>

using namespace std;

class Bundle {
    char name[128] = {};
    char username[128] = {};
    char password[128] = {};
    
public:
    Bundle() {};
    
    void setName(char* string){
        strcpy(name, string);
    }
    void setUsername(char* string){
        strcpy(username, string);
    }
    void setPassword(char* string){
        strcpy(password, string);
    }
    
    char* getName(){
        return name;
    }
    char* getUsername(){
        return username;
    }
    char* getPassword(){
        return password;
    }

    friend istream& operator >> (istream &inputStream, Bundle &bundle) {
        cout << "Enter name: ";
        cin >>  bundle.name;;
        cout << "Enter username: ";
        cin >>  bundle.username;;
        cout << "Enter password: ";
        cin >> bundle.password;
        
        return inputStream;
    }
    
    friend ostream& operator << (ostream &outputStream, const Bundle bundle) {
        cout << bundle.name
        << ": "
        << bundle.username
        << " | "
        << bundle.password
        << endl;
        
        return outputStream;
    }
    
    ~Bundle(){};
};

#endif /* Bundle_h */
