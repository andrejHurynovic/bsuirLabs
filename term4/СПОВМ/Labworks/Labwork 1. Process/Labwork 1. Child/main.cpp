//
//  main.cpp
//  Labwork 1. Child
//
//  Created by Andrej Hurynovič on 18.02.21.
//

#include <iostream>
#include <curses.h>

using namespace std;

int main(int argc, const char * argv[]) {
    initscr();
    printw("Parent:                     Child: \n");
    refresh();
    
    time_t now;
    for (int i = 0; i < 10; i++) {
        now = time(0);
        now += 86400;
        printw("                            %s", ctime(&now));
        refresh();
        napms(1000);
    }
    
    getch();
    return 0;
}
