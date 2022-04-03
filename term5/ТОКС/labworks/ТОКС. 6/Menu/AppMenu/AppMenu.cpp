//
//  AppMenu.cpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 23.11.21.
//

#include "AppMenu.hpp"

AppMenu::AppMenu() {
}

void AppMenu::interface() {
    clear_terminal();
    std::cout << "Station type:\n";
    std::cout << "1. Server.\n";
    std::cout << "2. Client.\n";
    std::cout << "3. Exit\n";
    
    unsigned int number = input_number(1, 3);
    if (number == 3)
        exit_menu();

    this->typeMenu = (number == 1) ? std::bind(&AppMenu::interface_server, this)
        : std::bind(&AppMenu::interface_client, this);

    (number == 1) ? set_menu_server() : set_menu_client();

    clear_terminal();
}

Package AppMenu::create_pack() {
    Package P;
    IPv4 sender(127, 0, 0, 1);
    IPv4 recipiend;
    std::cout << "Set recipiend: ";
    std::cin >> recipiend;

    P.change_sender(sender);
    P.change_recipiend(recipiend);

    char* data = input_line(MAX_SIZE_PACK_DATA);
    P.change_data(data);
    P.start();
    return P;
}

void AppMenu::start() {
    interface();

    unsigned int answer = 0;
    while (true) {
        try {
            this->typeMenu();
            answer = input_number();

            clear_terminal();
            check_input_excep();

            if (answer == this->menu.size() + 1)
                break;

            if (this->menu.find(answer) == menu.end())
                throw Error("ApplicationMenu::start", "Incorrect number");

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

void AppMenu::exit_menu() {
    clear_terminal();
    exit(0);
}
