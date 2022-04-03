//
//  MenuPS.hpp
//  main
//
//  Created by Andrej Hurynovič on 7.11.21.
//

#ifndef MenuPS_hpp
#define MenuPS_hpp

#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

#include "Pseudoterminal.hpp"
#include "Menu.hpp"

class AppMenuPS : public Menu {
private:
    Pseudoterminal Ps;
    std::map<int, std::function<void()>> menu;

public:
    AppMenuPS();
    
    void start() override;

private:
    void interface() override;

    void send_msg();
    void send_frame();

    void open_port();
    void close_port();

    void change_speed_in();
    void change_speed_out();

    void connect_port();
    void disconnect_port();

    void read_received_data();

private:
    std::string create_msg();

    void check_open_device();

private:
    std::string input_device_name();
};

#endif /* MenuPS_hpp */
