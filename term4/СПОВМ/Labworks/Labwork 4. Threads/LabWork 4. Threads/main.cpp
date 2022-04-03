//
//  main.cpp
//  LabWork 2. Synchronization
//
//  Created by Andrej Hurynovič on 2.03.21.
//

#include <iostream>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "signal.h"
#include "kbhit.h"

using namespace std;


void* printID(void *) {
        
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    
    while(true){
        sigwait(&set, NULL);
        pthread_t thread = pthread_self();
        string string = to_string(thread->_opaque_pthread_t::__sig);
        
        auto iterator = string.begin();
        do {
            cout << *iterator;
            fflush(stdout);
            iterator++;
            usleep(50000);
        } while(iterator!= string.end());
        
        cout << endl;
        
        kill(getpid(), SIGUSR2);
    }
}



int main(int argc, const char * argv[]) {
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    int currentThread = 0;
    
    vector<pthread_t> threads;
        
    keyboard keyboard;
    
    while(true) {
        if(keyboard.kbhit()){
            switch (keyboard.getch()) {
                case '+':
                    pthread_t thread;
                    pthread_create(&thread, NULL, printID, NULL);
//                    thread g( ) глянуть
                    threads.push_back(thread);
                    break;
                case '-':
                    if(!threads.empty()) {
                        pthread_cancel(*(threads.rbegin()));
                        pthread_join(*(threads.rbegin()), NULL);
                        threads.pop_back();
                    }
                    break;
                case 'q':
                    while(!threads.empty()) {
                        pthread_cancel(*(threads.rbegin()));
                        pthread_join(*(threads.rbegin()), NULL);
                        threads.pop_back();
                    }
                    return 0;
            }
        }
                
        if(!threads.empty()) {

            if(currentThread >= threads.size()){
                cout << endl;
                currentThread = 0;
            }
            usleep(10000);
            pthread_kill(threads[currentThread], SIGUSR1);
            currentThread++;
            
            sigwait(&set, NULL);
        }
    }
    
    
}
