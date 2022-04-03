//
//  PStatus.hpp
//  main
//
//  Created by Belousov Ilya on 4.11.21.
//

#ifndef PStatus_hpp
#define PStatus_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t STATUS_ADRESS_SIZE = 13;
const size_t STATUS_INFO_SIZE = 15;

const char collision[STATUS_INFO_SIZE] = "$$$$$$$$$$$$$$";

enum status_flags {
    connect = 0,
    disconnect,
    error,
};

struct status {
    char sender[STATUS_ADRESS_SIZE];
    char info[STATUS_INFO_SIZE];
    unsigned int flag;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->flag;
        ar & this->sender;
        ar & this->info;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->flag;
        ar & this->sender;
        ar & this->info;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    void set_connect(const std::string &device) {
        strcpy(this->sender, device.c_str());
        this->flag = connect;
    }

    void set_disconnect(const std::string &device) {
        strcpy(this->sender, device.c_str());
        this->flag = disconnect;
    }

    void set_error(const std::string &device) {
        strcpy(this->sender, device.c_str());
        strcpy(this->info, collision);
        this->flag = error;
    }
};



#endif /* PStatus_hpp */
