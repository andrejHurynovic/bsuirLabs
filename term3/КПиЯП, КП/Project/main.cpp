//
//  main.cpp
//  Project
//
//  Created by Andrej Hurynovič on 27.10.20.
//

#include "Menu.h"


int main(){

    Settings::getSettingsFromFile();

    Menu menu;
    menu.call();

}
