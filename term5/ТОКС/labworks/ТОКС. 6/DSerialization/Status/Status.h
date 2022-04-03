//
//  Header.h
//  LabWork_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#pragma once

#include "DSerialization.hpp"

#define PACKAGE_RECEIVED 1

struct Status {
    unsigned long recipient;
    unsigned long sender;
    unsigned int flag;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->recipient;
        ar & this->sender;
        ar & this->flag;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->recipient;
        ar & this->sender;
        ar & this->flag;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
};

const size_t MAX_SIZE_STATUS = (sizeof(Status) + 100) * 3;
