//
//  main.cpp
//  LabWork 2. Synchronization
//
//  Created by Andrej Hurynovič on 2.03.21.
//

#include <iostream>
#include <vector>
#include <unistd.h>
#include "signal.h"
#include "kbhit.h"




using namespace std;

int main(int argc, const char * argv[]) {

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    
    
    int currentProcess = 0;
    
    vector<pid_t> processes;
    
    keyboard keyboard;
    
    while(true) {
        if(keyboard.kbhit()){
            switch (keyboard.getch()) {
                case '+':
                    processes.push_back(fork());
                    
                    switch (*(processes.rbegin())) {
                        case -1:
                            perror("fork");
                            break;
                        case 0:
                            execv("/Users/andrejhurynovic/Library/Developer/Xcode/DerivedData/LabWork_2._Synchronization-bsudwveglqgkklayfluvhunkndnq/Build/Products/Debug/LabWork\ 2.\ Child", NULL);
                            break;
                        default:
                            break;
                    }
                    break;
                case '-':
                    if(!processes.empty()) {
                        kill(*(processes.rbegin()), SIGKILL);
                        waitpid(*(processes.rbegin()), 0, 0);
                        processes.pop_back();
                    }
                    break;
                case 'q':
                    while(!processes.empty()) {
                        kill(*(processes.rbegin()), SIGKILL);
                        waitpid(*(processes.rbegin()), 0, 0);
                        processes.pop_back();
                    }
                    return 0;
            }
        }
                
        
        
        
        if(!processes.empty()) {
            if(currentProcess >= processes.size()){
                cout << endl;
                fflush(stdout);
                currentProcess = 0;
            }
            usleep(100000);
            kill(processes[currentProcess], SIGUSR1);
          
            sigwait(&set, NULL);
            currentProcess++;
        }
    }
    
    
}
