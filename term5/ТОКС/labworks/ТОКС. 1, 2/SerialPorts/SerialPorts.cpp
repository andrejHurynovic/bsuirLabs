//
//  SerialPorts.cpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#include "SerialPorts.hpp"
#include <iostream>

SerialPorts::SerialPorts() {
    this->descriptor = -1;
    this->settings = nullptr;
}

SerialPorts::SerialPorts(std::string port) : SerialPorts() {
    this->port = port;
    openPort();
}

SerialPorts::~SerialPorts() {
    if (this->settings != nullptr)
        delete this->settings;
}

void SerialPorts::openPort() {
    if (this->port.empty())
        this->error("Func: open port\nPort name not specified.");

    this->descriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (!isOpen())
        this->error("Func: open_port\nInfo: Unable to open file.");

    fcntl(this->descriptor, F_SETFL, 0);

    this->initPortSettings();
}

void SerialPorts::openPort(const std::string port) {
    this->port = port;
    openPort();
}

void SerialPorts::closePort() {
    if (this->isOpen()) {
        close(this->descriptor);
        this->descriptor = -1;
    }
}

bool SerialPorts::isOpen() {
    return this->descriptor > 0;
}

void SerialPorts::error(const std::string msg) {
    throw msg;
}

size_t SerialPorts::writePort(const std::string str) {
    if (!this->isOpen())
        this->error("Func: read_port\nInfo: Port no open!");

    this->flushPortBuffer();
    return write(this->descriptor, str.c_str(), str.size());
}

std::string SerialPorts::readPort(const size_t size) {
    if (!this->isOpen())
        this->error("Func: write_port\nInfo: Port no open!");

    long n = 0;
    char buffer[size + 1];
    if ((n = read(this->descriptor, &buffer, size)) < 0)
        throw "Func: read port.\nInfo: Failed to read";
    buffer[size] += '\0';
    return buffer;
}

void SerialPorts::flushPortBuffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0) {
        this->error("Func: flush_port_buffer\nError: tcflush");
    }
}

void SerialPorts::initPortSettings() {
    int settingDescriptor = open(this->port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    this->settings = new PseudoPortSettings(settingDescriptor);
}


void SerialPorts::changeSpeed(const int &speed) {
    if (!isOpen())
        this->error("Func: Pseudoports::change_speed\nInfo: port no open.");

    this->settings->setInputSpeed(speed);
    this->settings->setInputSpeed(speed);
}
