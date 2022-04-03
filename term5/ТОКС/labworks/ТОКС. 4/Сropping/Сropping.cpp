//
//  Сropping.cpp
//  main
//
//  Created by Belousov Ilya on 31.10.21.
//

#include "Cropping.hpp"

void Cropping::start() noexcept{
    set_size_frame();
}

void Cropping::set_SDF() noexcept {

}

void Cropping::set_preamble() noexcept {
    this->value.preamble = fstart;
}

void Cropping::set_sender(const std::string &sender) noexcept {
    memcpy(this->value.SA, sender.c_str(), sizeof(this->value.SA));
}

void Cropping::set_recipiend(const std::string &recipiend) noexcept {
    memcpy(this->value.DA, recipiend.c_str(), sizeof(this->value.DA));
}

void Cropping::set_size_frame() noexcept {
    this->value.FCS = sizeof(this->value);
}

char* Cropping::get_data() noexcept {
    return this->value.data;
}

std::ostream& operator<<(std::ostream &out, Cropping &C) {
    out << C.value;
    return out;
}

