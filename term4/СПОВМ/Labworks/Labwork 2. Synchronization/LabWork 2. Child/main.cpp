//
//  main.cpp
//  LabWork 2. Child
//
//  Created by Andrej Hurynovič on 7.03.21.
//

#include <iostream>
#include <unistd.h>
#include "signal.h"


using namespace std;

int main(int argc, const char * argv[]) {
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    
    while(true){
        sigwait(&set, NULL);
        string string = to_string(getpid());
        
        auto iterator = string.begin();
        do {
            cout << *iterator;
            fflush(stdout);
            iterator++;
            usleep(100000);
        } while(iterator!= string.end());
        
        cout << endl;
        fflush(stdout);
        
        kill(getppid(), SIGUSR2);
    }
    return 0;
}
