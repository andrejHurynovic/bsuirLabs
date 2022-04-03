//
//  PseudoterminalSettings.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "PseudoterminalSettings.hpp"

PseudoterminalSettings::PseudoterminalSettings(const int &descriptor) {
    this->descriptor = descriptor;
    if (!this->is_open())
        Error::char_arr_error("Info: Setting port parameters\nError: The file descriptor is not valid!");

    this->clear_termios();
    this->get_old_param_terminal();

    this->set_all_flags();

    this->set_speed_in_port(B9600);
    this->set_speed_out_port(B9600);

    this->set_time_wait(1, 10);

    this->flush_port_buffer();
}

PseudoterminalSettings::~PseudoterminalSettings() {
    this->set_old_param_terminal();
}

void PseudoterminalSettings::set_all_flags() {
    this->get_param_terminal();
    this->set_iflags();
    this->set_lflags();
    this->set_oflags();
    this->set_сflags();
    this->set_param_terminal();
}

void PseudoterminalSettings::set_iflags() {
    this->newSettings.c_iflag |= (INPCK | ISTRIP);
    this->newSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
}

void PseudoterminalSettings::set_lflags() {
    this->newSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
}

void PseudoterminalSettings::set_oflags() {
    this->newSettings.c_oflag &= ~OPOST;
}

void PseudoterminalSettings::set_сflags() {
    this->newSettings.c_cflag |= (CLOCAL | CREAD);
    this->newSettings.c_cflag |= CS8;
}

void PseudoterminalSettings::set_speed_in_port(const speed_t &speed) {
    this->get_param_terminal();

    speed_t fspeed = find_speed(speed);
    if (fspeed < 0)
        return;
    
    if (cfsetispeed(&this->newSettings, fspeed))
        Error::char_arr_error("Func: set_speed_in_port\nError: cfsetispeed");

    this->set_param_terminal();
}
void PseudoterminalSettings::set_speed_out_port(const speed_t &speed) {
    this->get_param_terminal();

    speed_t fspeed = find_speed(speed);
    if (fspeed < 0)
        return;

    if (cfsetospeed(&this->newSettings, fspeed))
        Error::char_arr_error("Func: set_speed_out_port\nError: cfsetospeed");

    this->set_param_terminal();
}

void PseudoterminalSettings::set_time_wait(const cc_t &min, const cc_t &time) {
    this->get_param_terminal();

    this->newSettings.c_cc[VTIME] = time;
    this->newSettings.c_cc[VMIN] = min;

    this->set_param_terminal();
}

void PseudoterminalSettings::set_param_terminal() {
    if (tcsetattr(this->descriptor, TCSANOW, &this->newSettings))
        Error::char_arr_error("Func: set_old_param_terminal -> oldSettings");
}

void PseudoterminalSettings::get_param_terminal(){
    if (tcgetattr(this->descriptor, &this->newSettings))
        Error::char_arr_error("Func: get_old_param_terminal -> tcgetattr");
}

void PseudoterminalSettings::set_old_param_terminal() {
    if (tcsetattr(this->descriptor, TCSANOW, &this->oldSettings))
        Error::char_arr_error("Func: set_old_param_terminal -> oldSettings");
}

void PseudoterminalSettings::get_old_param_terminal() {
    if (tcgetattr(this->descriptor, &this->oldSettings))
        Error::char_arr_error("Func: get_old_param_terminal -> tcgetattr");
}

void PseudoterminalSettings::flush_port_buffer() {
    if (tcflush(this->descriptor, TCIFLUSH) < 0) {
        Error::char_arr_error("Func: flush_port_buffer\nError: tcflush");
    }
}

void PseudoterminalSettings::clear_termios() {
    bzero(&this->newSettings, sizeof(this->newSettings));
    bzero(&this->oldSettings, sizeof(this->oldSettings));
}

bool PseudoterminalSettings::is_open() {
    return descriptor > 0;
}

speed_t PseudoterminalSettings::find_speed(const speed_t &speed) const {
    switch (speed) {
        case 0:
            return B0;
        case 50:
            return B50;
        case 75:
            return B75;
        case 110:
            return B110;
        case 134:
            return B134;
        case 150:
            return B150;
        case 200:
            return B200;
        case 300:
            return B300;
        case 600:
            return B600;
        case 1200:
            return B1200;
        case 1800:
            return B1800;
        case 2400:
            return B2400;
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        default:
            Error::char_arr_error("Func: PseudoterminalSettings::find_speed\nInfo: Incorrectly set speed\n");
            break;
    }
    return -1;
}
