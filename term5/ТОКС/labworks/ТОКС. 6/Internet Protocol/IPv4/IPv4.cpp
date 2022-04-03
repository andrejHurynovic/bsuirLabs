//
//  IPv4.cpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#include "IPv4.hpp"

IPv4& IPv4::operator=(IPv4 const &other) noexcept {
    data = other.data;
    return *this;
}

std::string IPv4::to_string() const noexcept{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

unsigned long IPv4::to_unlong() const noexcept {
    return  (static_cast<unsigned long>(data[0]) << 24) |
            (static_cast<unsigned long>(data[1]) << 16) |
            (static_cast<unsigned long>(data[2]) << 8) |
             static_cast<unsigned long>(data[3]);
}

void IPv4::from_unlong(const unsigned long data) noexcept {
    unsigned char b1 = data >> 24;
    unsigned char b2 = data >> 16;
    unsigned char b3 = data >> 8;
    unsigned char b4 = data;
    this->data = std::array<unsigned char, 4>{{b1, b2, b3, b4}};
}

std::ostream& operator<<(std::ostream &os, const IPv4 &a) {
    os << static_cast<int>(a.data[0]) << '.'
       << static_cast<int>(a.data[1]) << '.'
       << static_cast<int>(a.data[2]) << '.'
       << static_cast<int>(a.data[3]);
    return os;
}

std::istream& operator>>(std::istream &is, IPv4 &a) {
    char d1, d2, d3;
    int b1, b2, b3, b4;

    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    if (d1 == '.' && d2 == '.' && d3 == '.')
        a = IPv4(b1, b2, b3, b4);
    else
        is.setstate(std::ios_base::failbit);
    return is;
}
