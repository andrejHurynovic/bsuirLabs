//
//  AppMenuServer.cpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#include "AppMenu.hpp"

void AppMenu::interface_server() {
    std::cout << "Port type: Server.\n";
    std::cout << "\t---Menu---\n";
    std::cout << "1. Open.\n";
    std::cout << "2. Send pack.\n";
    std::cout << "3. Get pack.\n";
    std::cout << "4. Set queue.\n";
    std::cout << "5. Set queue.\n";
    std::cout << "6. Accept connect.\n";
    std::cout << "7. Exit.\n";
}

void AppMenu::set_menu_server() {
    this->menu = {
        {1, std::bind(&AppMenu::open, this)},
        {2, std::bind(&AppMenu::send_pack_server, this)},
        {3, std::bind(&AppMenu::get_pack_server, this)},
        {4, std::bind(&AppMenu::set_queue, this)},
        {5, std::bind(&AppMenu::close, this)},
        {6, std::bind(&AppMenu::accept_connect, this)},
    };
}

void AppMenu::open() {
    if (this->station.is_open())
        throw Error("AppMenu::close(): the port is already open.");

    std::cout << "Waiting for stations to connect...\n";
    this->station.start();
    std::cout << "Connected!" << std::endl;
}

void AppMenu::set_queue() {
    std::cout << "Set queue\n";
    this->station.set_queue_connect(input_number(1, 20));
}

void AppMenu::close() {
    if (!this->station.is_open())
        throw Error("AppMenu::close(): the port is already closed.");
    this->station.stop();
}

void AppMenu::get_pack_server() {
    std::cout << "Waiting for package to be received...\n";
    std::cout << this->station.get_pack();
    std::cout << "Package received successfully!\n";
}

void AppMenu::send_pack_server() {
    Package P = create_pack();
    this->station.send_pack(P);
    std::cout << "The package was sent successfully!\n";
}

void AppMenu::accept_connect() {
    this->station.accept_connection();
    std::cout << "Station successfully connected!\n";
}
