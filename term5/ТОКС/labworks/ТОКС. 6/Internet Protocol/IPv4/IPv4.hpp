//
//  IPv4.hpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef IPv4_hpp
#define IPv4_hpp

#include <array>
#include <string>
#include <sstream>

class IPv4 {
private:
    std::array<unsigned char, 4> data;
public:
    constexpr IPv4() : data{ {0} } {}
    constexpr IPv4(unsigned char const a, unsigned char const b,
                   unsigned char const c, unsigned char const d)
                         : data{{a, b, c, d}} {}

    constexpr IPv4(IPv4 const &other) noexcept : data(other.data) {}

    IPv4& operator=(IPv4 const &other) noexcept;

    std::string to_string() const noexcept;
    unsigned long to_unlong() const noexcept;

    void from_unlong(const unsigned long data) noexcept;

    friend std::ostream& operator<<(std::ostream &os, const IPv4 &a);
    friend std::istream& operator>>(std::istream &is, IPv4 &a);
};

#endif /* IPv4_hpp */
