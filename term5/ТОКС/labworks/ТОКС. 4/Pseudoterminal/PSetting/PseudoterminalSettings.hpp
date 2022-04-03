//
//  PseudoterminalSettings.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef PseudoterminalSettings_hpp
#define PseudoterminalSettings_hpp

#include <termios.h>
#include <string>
#include <iostream>
#include <map>

#include "Error.hpp"

class PseudoterminalSettings {
private:
    int descriptor;
    struct termios oldSettings;
    struct termios newSettings;

public:
    PseudoterminalSettings();
    PseudoterminalSettings(const int &descriptor);
    ~PseudoterminalSettings();

    bool is_open();

    void set_speed_out_port(const speed_t &speed);
    void set_speed_in_port(const speed_t &speed);

    void set_time_wait(const cc_t &min, const cc_t &time);

    void get_param_terminal();
    void get_old_param_terminal();

    void flush_port_buffer();

private:
    void set_all_flags();
    void set_сflags();
    void set_lflags();
    void set_iflags();
    void set_oflags();

    void set_param_terminal();
    void set_old_param_terminal();

    void clear_termios();

    speed_t find_speed(const speed_t &speed) const;
};

#endif /* PseudoterminalSettings_hpp */
