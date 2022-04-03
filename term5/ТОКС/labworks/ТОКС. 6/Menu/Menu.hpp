//
//  Menu.hpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "Error.hpp"

#include <iostream>

class Menu {
protected:
//    virtual void set_menu() = 0;


public:
    virtual void start() = 0;
    virtual void interface() = 0;

protected:
    int input_number() const;
    int input_number(const int &min, const int &max) const;
    std::string input_line() const;
    char* input_line(const size_t &size) const;

protected:
    bool check_input_bool() const;
    void check_input_excep() const;
    void clear_buffer() const;
    void clear_terminal() const;
    void confirmation() const;
};

#endif /* Menu_hpp */
