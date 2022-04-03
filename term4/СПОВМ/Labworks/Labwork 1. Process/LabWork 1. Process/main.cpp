//
//  main.cpp
//  LabWork 1. Process
//
//  Created by Andrej Hurynovič on 16.02.21.
//

#include <iostream>
#include <curses.h>

#include <sys/wait.h>
#include <unistd.h>

void printTime(){
    initscr();
    
    time_t now;                     //вывод id процесса по символам
    for (int i = 0; i < 10; i++) {
        now = time(0);
        printw("%s", ctime(&now));
        refresh();
        napms(1000);
    }
}


int main(int argc, const char * argv[]) {
    
    int pid = fork();               //почитай про эту функцию в методе
    
        
    if(pid == -1){                  //если ошибка
        return 0;
    }
    
    if(pid == 0){                   //если я ребёнок
        execv("/Users/andrejhurynovic/Library/Developer/Xcode/DerivedData/LabWork_1._Process-digbmlnbsubudgcuvmbazhwnhzkl/Build/Products/Debug/Labwork\ 1.\ Child", NULL);  //это заменить на /child или типа такого, зависит от того, как ты наз. файл исполняемый ребёнка
    }else{                          //если я родитель
        printTime();
        
        int status;
        waitpid(pid, &status, 0);   //ожидание завершения процесса с таким pid
        endwin();                   //закончить работу с окном curces
        return 0;
    }
}
