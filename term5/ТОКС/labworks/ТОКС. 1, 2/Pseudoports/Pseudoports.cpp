//
//  Pseudoports.cpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#include "Pseudoports.hpp"

Pseudoports::Pseudoports() {
    this->masterDescriptor = -1;
    this->settings = nullptr;
}

Pseudoports::~Pseudoports() {
    if (this->settings != nullptr)
        delete this->settings;
}

std::string Pseudoports::create_port() {
    if (this->isOpen())
        this->error("Info: The pseudo terminal has already been created!");

    this->masterDescriptor = posix_openpt(O_RDWR | O_NOCTTY | O_NDELAY);
    fcntl(this->masterDescriptor, F_SETFL, 0);
    if (this->masterDescriptor < 0) this->error("Func: create port\nInfo: open port");

    if (grantpt(this->masterDescriptor) < 0)
        this->error("Func: create port\nInfo: grantpt");


    if (unlockpt(this->masterDescriptor) < 0)
        this->error("Func: create port\nInfo: unlockpt");

    this->port = ptsname(this->masterDescriptor);
    if (this->port.empty())
        this->error("Func: create port\nInfo: ptsname");

    this->initPortSettings();

    return this->port;
}

void Pseudoports::closePort() {
    if (this->isOpen()) {
        close(this->masterDescriptor);
        this->masterDescriptor = -1;
        this->port.clear();
    }
}

bool Pseudoports::isOpen() {
    return this->masterDescriptor > 0;
}

void Pseudoports::error(std::string msg) {
    throw msg;
}

std::string Pseudoports::getPortName() {
    return this->port;
}

std::string Pseudoports::readPort(const size_t size) {
    if (!this->isOpen())
        this->error("Func: read port\nInfo: Port no open!");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->masterDescriptor, &buffer, size)) < 0)
        this->error("Func: read port.\nInfo: Failed to read");
    buffer[n] += '\0';
    return buffer;
}

size_t Pseudoports::writePort(const std::string str) {
    if (!this->isOpen())
        this->error("Func: write port\nInfo: Port no open!");

    this->flushPortBuffer();
    return write(this->masterDescriptor, str.c_str(), str.size());
}

void Pseudoports::initPortSettings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoPortSettings(settingDescriptor);
}

void Pseudoports::flushPortBuffer() {
    if (tcflush(this->masterDescriptor, TCIFLUSH) < 0) {
        this->error("Func: flush_port_buffer\nError: tcflush");
    }
}

void Pseudoports::changeSpeed(const int &speed) {
    if (!isOpen())
        this->error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->setInputSpeed(speed);
    this->settings->setOutputSpeed(speed);
}
