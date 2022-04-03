//
//  Package.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include "Package.hpp"

void Package::set_sender(const std::string &sender) noexcept {
    memcpy(this->value.sender, sender.c_str(), sizeof(this->value.sender));
}

void Package::set_recipiend(const std::string &recipiend) noexcept {
    memcpy(this->value.recipient, recipiend.c_str(), sizeof(this->value.recipient));
}

void Package::set_size_pack() noexcept {
    this->value.sizePack = sizeof(this->value);
}

void Package::set_flag() noexcept {
    this->value.fstart = this->fstart;
}

void Package::set_other_flag() noexcept {

}

void Package::start() noexcept {
    set_flag();
//    set_other_flag();
    set_size_pack();
}

char* Package::get_data() noexcept {
    return this->value.data;
}

std::ostream& operator<<(std::ostream &out, Package &P) {
    out << P.value;
    return out;
}




