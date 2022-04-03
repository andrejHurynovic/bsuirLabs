//
//  main.cpp
//  LabWork 3. Server
//
//  Created by Andrej Hurynovič on 12.03.21.
//

#include <iostream>
#include <signal.h>
#include <sys/sem.h>
#include <unistd.h>


//rwx dec    meaning
//--- ---    -------
//001 01   = execute
//010 02   = write
//011 03   = write & execute
//100 04   = read
//101 05   = read & execute
//110 06   = read & write
//111 07   = read & write & execute

//user,group,other == 644

using namespace std;

int main (int argc, char ** argv) {
    //temp
    
    sembuf sembuf;
    int semaphore = semget(ftok("/Users/andrejhurynovic/Library/Developer/Xcode/DerivedData/LabWork_3._Process_interaction-exveyzmiuaczyqcfrlchklmkuuvk/Build/Products/Debug/LabWork 3. Process interaction", 234), 2, IPC_CREAT | 0600);

    //0 - Message sended
    //1 - Message readed

    
    if(semaphore == -1) {
        perror("semget");
    }
    

    int pipeDescriptor[2] = {};
    
    if((pipe(pipeDescriptor) == -1)){
        perror("pipe");
        return 0;
    }
    
    pid_t pid = fork();
    
    if(pid == 0){
        close(pipeDescriptor[1]);
        
        while(true){
            sembuf.sem_num = 0;
            sembuf.sem_op = -1;
            semop(semaphore, &sembuf, 1);
            
            int stringLenght = 0;
            read(pipeDescriptor[0], (char*)&stringLenght, sizeof(int));
            
            char* reciveString = new char [stringLenght + 1];

            read(pipeDescriptor[0], (char*)reciveString, (stringLenght + 1));

            
            cout << endl << "Client: Incoming message (" << stringLenght << "): " << reciveString << endl << "Press key to continue: ";
                        
            fflush(stdin);
            getchar();
            
            delete[] reciveString;
            
            sembuf.sem_num = 1;
            sembuf.sem_op = 1;
            semop(semaphore, &sembuf, 1);
        }
    }
    
    close(pipeDescriptor[0]);
    
    while(true) {
        cout << "Server: Send message (S), Quit (Q)" << endl;
        fflush(stdin);
        switch (getchar()) {
            case 'Q':
                kill(pid, SIGKILL);
                waitpid(pid, NULL, NULL);
                
                close(pipeDescriptor[1]);
                return 0;
                break;
            case 'S':{
                cout << "Enter message: ";
                string messageString;
                fflush(stdin);
                getline(cin, messageString);
                
                int stringLenght = messageString.length();
                
                write(pipeDescriptor[1], (char*)&stringLenght, sizeof(int));
                write(pipeDescriptor[1], messageString.c_str(), stringLenght);
                
                sembuf.sem_num = 0;
                sembuf.sem_op = 1;
                semop(semaphore, &sembuf, 1);
                
                sembuf.sem_num = 1;
                sembuf.sem_op = -1;
                semop(semaphore, &sembuf, 1);
            }
            default:
                break;
        }
    }
}

