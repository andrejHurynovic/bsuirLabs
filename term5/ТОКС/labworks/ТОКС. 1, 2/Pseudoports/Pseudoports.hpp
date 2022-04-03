//
//  Pseudoports.hpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#ifndef Pseudoports_hpp
#define Pseudoports_hpp

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "PseudoPortSettings.hpp"
#include "Package.hpp"

class Pseudoports {
private:
    int masterDescriptor;
    std::string port;

    PseudoPortSettings *settings;

public:
    Pseudoports();
    ~Pseudoports();

    std::string create_port();
    void closePort();
    bool isOpen();

    std::string getPortName();
    void changeSpeed(const int &speed);

    std::string readPort(const std::size_t size);
    size_t writePort(const std::string str);

private:
    void initPortSettings();
    void flushPortBuffer();
    void error(std::string msg);
};



#endif /* Pseudoports_hpp */
