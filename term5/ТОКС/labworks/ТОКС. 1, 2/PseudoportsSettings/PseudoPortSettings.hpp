//
//  PseudoPSettings.hpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#ifndef PseudoPSettings_hpp
#define PseudoPSettings_hpp

#include <termios.h>
#include <string>

class PseudoPortSettings {
private:
    int descriptor;
    struct termios oldSettings;
    struct termios newSettings;

public:
    PseudoPortSettings();
    PseudoPortSettings(int descriptor);
    ~PseudoPortSettings();

    bool isOpen();

    void setOutputSpeed(const speed_t speed);
    void setInputSpeed(const speed_t speed);

    void setWaitTime(const cc_t min, const cc_t time);

    void getParametersTerminal();
    void getOldParametersTerminal();

    void flushPortBuffer();

private:
    void setAllFlags();
    void setCFlags();
    void setLFlags();
    void setIFlags();
    void setOFlags();

    void setParametersTerminal();
    void setOldParametersTerminal();

    void clearTermios();

    void error(const std::string msg);
};

#endif /* PseudoPSettings_hpp */
