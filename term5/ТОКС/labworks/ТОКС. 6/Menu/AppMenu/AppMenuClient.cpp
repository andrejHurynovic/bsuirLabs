//
//  AppMenuClient.cpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 23.11.21.
//

#include "AppMenu.hpp"

void AppMenu::interface_client() {
    std::cout << "Port type: Client.\n";
    std::cout << "\t---Menu---\n";
    std::cout << "1. Connect.\n";
    std::cout << "2. Send pack.\n";
    std::cout << "3. Get pack.\n";
    std::cout << "4. Disconnect.\n";
    std::cout << "5. Exit.\n";
}

void AppMenu::set_menu_client() {
    this->menu = {
        {1, std::bind(&AppMenu::connect, this)},
        {2, std::bind(&AppMenu::send_pack_client, this)},
        {3, std::bind(&AppMenu::get_pack_client, this)},
        {4, std::bind(&AppMenu::disconnect, this)},
    };
}


void AppMenu::connect() {
    this->set_ip();
    this->client.start();
}

void AppMenu::disconnect() {

}

void AppMenu::set_ip() {
    IPv4 ip;
    std::cout << "Set ip: ";
    std::cin >> ip;

    this->client.set_ip(ip);
}

void AppMenu::get_pack_client() {
    std::cout << "Waiting for package to be received...\n";
    std::cout << this->client.get_pack();
    std::cout << "Package received successfully!\n";
}

void AppMenu::send_pack_client() {
    Package P = create_pack();
    this->client.send_pack(P);
    std::cout << "The package was sent successfully!\n";
}
