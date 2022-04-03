//
//  MenuSM.hpp
//  main
//
//  Created by Andrej Hurynovič on 18.11.21.
//

#ifndef MenuSM_hpp
#define MenuSM_hpp

#include "Menu.hpp"

#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

#include "StationMonitor.hpp"

class AppMenuSM : public Menu {
private:
    StationMonitor Sm;
    std::map<int, std::function<void()>> menu;

public:
    AppMenuSM();
    void start() override;

private:
    void interface() override;

    void open_port();
    void close_port();

    void change_speed_in();
    void change_speed_out();

    void connect_port();
    void disconnect_port();

    void priority_mode();
    void early_release_regime();

private:
    void check_open_device();

private:
    std::string input_device_name();
};

#endif /* MenuSM_hpp */
