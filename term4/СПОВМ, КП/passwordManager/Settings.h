#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

enum KeyLenght {
    bits128 = 128,
    bits192 = 192,
    bits256 = 256
};

class Settings {
protected:
    static KeyLenght keySize;
    static bool openOnEnter;
    
public:
    static char specialString[];

    Settings();
    static void loadSettings();
    static void saveSettings();
    static void setTheDefaultSettings();
    
    static void setKeySize(KeyLenght);
    static void setOpenOnEnter(bool);
    
    static KeyLenght getKeySize();
    static bool getOpenOnEnter();
};

#endif // SETTINGS_H
