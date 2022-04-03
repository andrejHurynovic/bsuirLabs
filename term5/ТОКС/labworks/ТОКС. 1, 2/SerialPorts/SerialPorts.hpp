//
//  SerialPorts.hpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#ifndef SerialPorts_hpp
#define SerialPorts_hpp

#include <string>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "PseudoPortSettings.hpp"
#include "Package.hpp"

class SerialPorts
{
private:
    int descriptor;
    std::string port;

    PseudoPortSettings *settings;

public:
    SerialPorts();
    SerialPorts(std::string port);
    ~SerialPorts();

    void startPort();

    void openPort();
    void openPort(const std::string port);

    void closePort();
    bool isOpen();

    size_t writePort(const std::string str);
    std::string readPort(const size_t size);

    
    void changeSpeed(const int &speed);
private:
    void flushPortBuffer();
    void initPortSettings();
//    bool change_law_port(const fs::path path, const mode_t mode);
    void error(const std::string msg);
};
	
#endif
