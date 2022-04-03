//
//  Access.hpp
//  main
//
//  Created by Andrej Hurynovič on 15.11.21.
//

#ifndef Access_hpp
#define Access_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#define TOKEN_BIT_MARKER 0
#define TOKEN_BIT_FRAME 1

#define PRIORITY_BITS_OFF 0

struct Access {
    unsigned short PriorityBits;
    unsigned short TokenBit;
    unsigned short MonitorBit;
    unsigned short ReservationBits;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->PriorityBits;
        ar & this->TokenBit;
        ar & this->MonitorBit;
        ar & this->ReservationBits;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->PriorityBits;
        ar & this->TokenBit;
        ar & this->MonitorBit;
        ar & this->ReservationBits;
    }

    void set_priority_bit(const unsigned int &priority) {
        this->PriorityBits = priority;
    }

    void set_token_bit(const unsigned int &token) {
        this->TokenBit = token;
    }

    void set_reservation_bit(const unsigned int &reserv) {
        this->ReservationBits = reserv;
    }

    unsigned int get_priority_bit() const {
        return this->PriorityBits;
    }

    unsigned int get_token_bit() const {
        return this->TokenBit;
    }

    unsigned int get_reservation_bit() const {
        return this->ReservationBits;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, const struct Access &A) {
        out << "Priority Bits: " << A.PriorityBits << "\n";
        out << "Token Bit: " << A.TokenBit << "\n";
        out << "Monitor Bit: " << A.MonitorBit << "\n";
        out << "Reservation Bits: " << A.ReservationBits << "\n";
        return out;
    }
};

#endif /* Access_hpp */
