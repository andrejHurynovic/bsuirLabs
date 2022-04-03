//
//  Status.hpp
//  main
//
//  Created by Andrej Hurynovič on 4.11.21.
//

#ifndef Status_hpp
#define Status_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t STATUS_ADRESS_SIZE = 13;
const size_t STATUS_INFO_SIZE = 15;

const char collision[STATUS_INFO_SIZE] = "$$$$$$$$$$$$$$";

enum status_flags {
    connect = 0,
    disconnection,
    error,
};

struct Status {
    unsigned int Flag;

    Status() = default;
    Status(const unsigned int &flag) {
        if (connect == flag)
            this->Flag = connect;
        else if (disconnection == flag)
            this->Flag = disconnection;
        else if (error == flag)
            this->Flag = error;
    }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->Flag;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->Flag;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    void set_connect() {
        this->Flag = connect;
    }

    void set_disconnect() {
        this->Flag = disconnection;
    }

    void set_error() {
        this->Flag = error;
    }
};

#endif /* Status_hpp */
