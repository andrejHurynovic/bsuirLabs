//
//  Pack.hpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef Pack_hpp
#define Pack_hpp

#include "DSerialization.hpp"

const size_t MAX_SIZE_PACK_DATA = 1024;

struct Pack {
    unsigned long fstart;
    unsigned long recipient;
    unsigned long sender;
    unsigned long fother;
    size_t sizeData;
    char data[MAX_SIZE_PACK_DATA];
    size_t sizePack;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->fstart;
        ar & this->recipient;
        ar & this->sender;
        ar & this->fother;
        ar & this->sizeData;
        ar & this->data;
        ar & this->sizePack;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->fstart;
        ar & this->recipient;
        ar & this->sender;
        ar & this->fother;
        ar & this->sizeData;
        ar & this->data;
        ar & this->sizePack;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
    friend std::ostream& operator<<(std::ostream &out, struct Pack &P) {
        out << "\t---PACK---\n";
        out << "Fstart: " << P.fstart << "\n";
        out << "Recipient: " << P.recipient << "\n";
        out << "Sender: " << P.sender << "\n";
        out << "Fother: " << P.fother << "\n";
        out << "Size data: " << P.sizeData << "\n";
        out << "Data: " << P.data << "\n";
        out << "Size pack: " << P.sizePack << "\n";
        out << "\t---END PACK---\n";
        return out;
    }
};

#endif /* Pack_hpp */
