//
//  AppMenu.hpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef AppMenu_hpp
#define AppMenu_hpp

#include "Menu.hpp"
#include "Station.hpp"
#include "Client.hpp"

#include <map>
#include <memory>

#include <boost/exception/diagnostic_information.hpp>

class AppMenu : protected Menu {
private:
    std::map<unsigned int, std::function<void()>> menu;
    std::function<void()> typeMenu;
    Station station;
    Client client;

public:
    AppMenu();

    void start() override;

private:
    void interface() override;
    void interface_server();
    void interface_client();

    void set_menu_server();
    void set_menu_client();

    void send_pack_server();
    void get_pack_server();
    void send_pack_client();
    void get_pack_client();

    Package create_pack();
    void accept_connect();

    void connect();
    void disconnect();

    void set_ip();

    void open();
    void close();

    void set_queue();

    void exit_menu();
//protected:
//    void set_menu() override;
};

#endif /* AppMenu_hpp */
