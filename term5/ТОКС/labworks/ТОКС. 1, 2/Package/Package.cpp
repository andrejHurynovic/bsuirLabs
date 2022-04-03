//
//  Package.cpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#include "Package.hpp"



void Package::set_size_pack() noexcept {
    this->value.packSize = sizeof(this->value);
}

void Package::setFlag() noexcept {
    this->value.startPoint = this->fstart;
}

void Package::set_other_flag() noexcept {

}

void Package::start() noexcept {
    setFlag();
//    set_other_flag();
    set_size_pack();
}

char* Package::getData() noexcept {
    return this->value.data;
}

std::ostream& operator<<(std::ostream &out, Package &pack) {
    out << pack.value;
    return out;
}


