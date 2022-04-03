//
//  MenuSM.cpp
//  main
//
//  Created by Andrej Hurynovič on 18.11.21.
//

#include "MenuSM.hpp"

AppMenuSM::AppMenuSM() {
    this->menu = {
        {1, std::bind(&AppMenuSM::open_port, this)},
        {2, std::bind(&AppMenuSM::change_speed_in, this)},
        {3, std::bind(&AppMenuSM::change_speed_out, this)},
        {4, std::bind(&AppMenuSM::close_port, this)},

        {5, std::bind(&AppMenuSM::connect_port, this)},
        {6, std::bind(&AppMenuSM::disconnect_port, this)},

        {7, std::bind(&AppMenuSM::priority_mode, this)},
        {8, std::bind(&AppMenuSM::early_release_regime, this)},
    };
}

std::string AppMenuSM::input_device_name() {
    std::cout << "Input device name: ";
    return input_line(ADRESS_SIZE);
}

void AppMenuSM::interface() {
    std::cout << "Stantion monitor name: " << this->Sm.get_port_name();
    std::cout << "\nEarly mode: " << std::boolalpha << this->Sm.get_early_release_regime();
    std::cout << "\nPriority mode: " << std::boolalpha << this->Sm.get_priority_mode();
    std::cout << "\n\t---Menu---\n";
    std::cout << "1. Create station.\n";
    std::cout << "2. Change speed in station.\n";
    std::cout << "3. Change speed out station.\n";
    std::cout << "4. Close port\n";
    std::cout << "\n";
    std::cout << "5. Connect device.\n";
    std::cout << "6. Disconnect device.\n";
    std::cout << "\n";
    std::cout << "7. Priority mode.\n";
    std::cout << "8. Ring mode.\n";
    std::cout << "\n";
    std::cout << "9. Exit.\n";
}

void AppMenuSM::open_port() {
    this->Sm.create_port();
    std::cout << "The port was created: " << this->Sm.get_port_name() << std::endl;
}

void AppMenuSM::change_speed_in() {
    check_open_device();
    std::cout << "\tSet speed in\n";
    Sm.change_speed_in(input_number());
}

void AppMenuSM::change_speed_out() {
    check_open_device();
    std::cout << "\tSet speed out\n";
    Sm.change_speed_out(input_number());
}

void AppMenuSM::close_port() {
    if (!Sm.is_open())
        throw Error("ApplicationMenuSM::close_port: The port is already closed!\n");

    this->Sm.stop();
    std::cout << "Port closed successfully" << std::endl;
}

void AppMenuSM::connect_port() {
    check_open_device();

    std::cout << "\tDevice name\n";
    std::string device = input_line();

    if (!Sm.connect(device))
        throw Error("ApplicationMenuSM::connect_port: Connection failed!");

    std::cout << "Connection successful!\n";
    Sm.send_marker();
}

void AppMenuSM::disconnect_port() {
    Sm.disconnect();
    std::cout << "Device disconnected successfully!\n";
}

void AppMenuSM::check_open_device() {
    if (!Sm.is_open())
        throw Error("ApplicationMenuSM::check_open_device: The port has not been created!");
}

void AppMenuSM::priority_mode() {
    std::cout << "Enable priority mode?\n";
    std::cout << "1. Yes" << " " << "2. No\n";
    int answer = input_number(1, 2);
    if (answer == 2) {
        Sm.set_priority_mode(0);
        return;
    }

    std::cout << "Enter the priority level (1 - 8)\n";
    this->Sm.set_priority_mode(input_number(1, 8));
}

void AppMenuSM::early_release_regime() {
    std::cout << "Enable early release mode?\n";
    std::cout << "1. Yes" << " " << "2. No\n";
    int answer = input_number(1, 2);
    if (answer == 2) {
        Sm.set_early_release_regime(0);
        return;
    }
    Sm.set_early_release_regime(1);
}

void AppMenuSM::start() {
    clear_terminal();
    unsigned int answer = 0;
    while (true) {
        try {
            interface();
            answer = input_number(1, (int)this->menu.size() + 1);
            clear_terminal();
            if ((int)this->menu.size() + 1 == answer)
                break;

            menu[answer]();
        } catch (const Error &ex) {
            std::cerr << "\t---Error---\n";
            std::cerr << "What: " << ex.what() << "\n";
            std::cerr << "\t---End---\n\n";

        } catch (const boost::archive::archive_exception &ex) {
            std::cerr << "\t---Error boost---\n";
            std::cerr << "What: " << boost::diagnostic_information(ex);
            std::cerr << "\t---End---\n\n";

        }
        confirmation();
    }
}

