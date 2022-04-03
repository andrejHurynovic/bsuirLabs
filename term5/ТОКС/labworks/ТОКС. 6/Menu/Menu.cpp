//
//  Menu.cpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#include "Menu.hpp"

int Menu::input_number() const {
    int number;
    do {
        std::cout << "Input number: ";
        std::cin >> number;
    } while (!check_input_bool());
    return number;
}

int Menu::input_number(const int &min, const int &max) const {
    int number = 0;
    do {
        number = input_number();
    } while (number < min || number > max);
    
    return number;
}

void Menu::clear_buffer() const {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ios_base::clear();
}

void Menu::clear_terminal() const {
    system("clear");
}

void Menu::confirmation() const {
    std::cout << "\nconfirm to continue...";
    clear_buffer();
    getchar();
    clear_terminal();
}

std::string Menu::input_line() const {
    clear_buffer();
    std::string line;
    std::cout << "Input line: ";
    std::cin >> line;
    return line;
}

char* Menu::input_line(const size_t &size) const {
    clear_buffer();
    char line[size];
    std::cout << "Input line: ";
    std::cin.getline(line, size);
    return line;
}

void Menu::check_input_excep() const{
    if (std::cin.ios_base::fail()) {
        clear_buffer();
        throw Error("Menu::check_input_excep: Not a number entered");
    }
}

bool Menu::check_input_bool() const{
    if (std::cin.ios_base::fail()) {
        clear_buffer();
        std::cerr << "Menu::check_input_bool: Not a number entered" << std::endl;
        return false;
    }
    return true;
}
