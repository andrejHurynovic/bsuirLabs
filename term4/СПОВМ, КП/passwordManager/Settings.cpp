#include "Settings.h"

void Settings::loadSettings() {
    QSettings settings;
    
    if(settings.value("bits") == "128"){
        Settings::setKeySize(bits128);
    }
    if(settings.value("bits") == "192"){
        Settings::setKeySize(bits192);
    }
    if(settings.value("bits") == "256"){
        Settings::setKeySize(bits256);
    }
    
    if(settings.value("open") == "true"){
        Settings::setOpenOnEnter(true);
    }
    
    if(settings.value("open") == "false"){
        Settings::setOpenOnEnter(false);
    }
}

void Settings::saveSettings() {
    QSettings settings;
    
    switch (Settings::getKeySize()) {
        case bits128:
            settings.setValue("bits", "128");
            break;
        case bits192:
            settings.setValue("bits", "192");
            break;
        case bits256:
            settings.setValue("bits", "256");
            break;
    }
    
    if(Settings::getOpenOnEnter()){
        settings.setValue("open", "true");
    } else {
        settings.setValue("open", "false");
    }
    
}

void Settings::setTheDefaultSettings() {
    keySize = bits256;
    openOnEnter = false;
    saveSettings();
}

void Settings::setKeySize(enum KeyLenght keyLenght){
    keySize = keyLenght;
}

void Settings::setOpenOnEnter(bool temp){
    openOnEnter = temp;
}

enum KeyLenght Settings::getKeySize(){
    return keySize;
}

bool Settings::getOpenOnEnter( ){
    return openOnEnter;
}


enum KeyLenght Settings::keySize = bits256;
bool Settings::openOnEnter = false;
