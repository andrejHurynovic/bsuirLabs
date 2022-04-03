//
//  PseudoPSettings.cpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#include "PseudoPortSettings.hpp"

PseudoPortSettings::PseudoPortSettings(const int descriptor) {
    this->descriptor = descriptor;
    if (!this->isOpen()) this->error("Info: Setting port parameters\nError: The file descriptor is not valid!");

    this->clearTermios();
    this->getOldParametersTerminal();

    this->setAllFlags();

    this->setInputSpeed(B9600);
    this->setOutputSpeed(B9600);

    this->setWaitTime(1, 10);

    this->flushPortBuffer();
}

PseudoPortSettings::~PseudoPortSettings() {
    this->setOldParametersTerminal();
}

void PseudoPortSettings::setAllFlags() {
    this->getParametersTerminal();
    this->setIFlags();
    this->setLFlags();
    this->setOFlags();
    this->setCFlags();
    this->setParametersTerminal();
}

void PseudoPortSettings::setIFlags() {
    this->newSettings.c_iflag |= (INPCK | ISTRIP);
    this->newSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
}

void PseudoPortSettings::setLFlags() {
    this->newSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
}

void PseudoPortSettings::setOFlags() {
    this->newSettings.c_oflag &= ~OPOST;
}

void PseudoPortSettings::setCFlags() {
    this->newSettings.c_cflag |= (CLOCAL | CREAD);
    this->newSettings.c_cflag |= CS8;
}

void PseudoPortSettings::setInputSpeed(const speed_t speed) {
    this->getParametersTerminal();

    if (cfsetispeed(&this->newSettings, speed))
        this->error("Func: set_speed_in_port\nError: cfsetispeed");

    this->setParametersTerminal();
}
void PseudoPortSettings::setOutputSpeed(const speed_t speed) {
    this->getParametersTerminal();

    if (cfsetospeed(&this->newSettings, speed))
        this->error("Func: set_speed_out_port\nError: cfsetospeed");

    this->setParametersTerminal();
}

void PseudoPortSettings::setWaitTime(const cc_t min, const cc_t time) {
    this->getParametersTerminal();

    this->newSettings.c_cc[VTIME] = time;
    this->newSettings.c_cc[VMIN] = min;

    this->setParametersTerminal();
}

void PseudoPortSettings::setParametersTerminal() {
    if (tcsetattr(this->descriptor, TCSANOW, &this->newSettings))
        this->error("Func: set_old_param_terminal -> oldSettings");
}

void PseudoPortSettings::getParametersTerminal() {
    if (tcgetattr(this->descriptor, &this->newSettings))
        this->error("Func: get_old_param_terminal -> tcgetattr");
}

void PseudoPortSettings::setOldParametersTerminal() {
    if (tcsetattr(this->descriptor, TCSANOW, &this->oldSettings))
        this->error("Func: set_old_param_terminal -> oldSettings");
}

void PseudoPortSettings::getOldParametersTerminal() {
    if (tcgetattr(this->descriptor, &this->oldSettings))
        this->error("Func: get_old_param_terminal -> tcgetattr");
}

void PseudoPortSettings::flushPortBuffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0) {
        this->error("Func: flush_port_buffer\nError: tcflush");
    }
}

void PseudoPortSettings::clearTermios() {
    bzero(&this->newSettings, sizeof(this->newSettings));
    bzero(&this->oldSettings, sizeof(this->oldSettings));
}

bool PseudoPortSettings::isOpen() {
    return descriptor > 0;
}

void PseudoPortSettings::error(const std::string msg) {
    throw msg;
}
