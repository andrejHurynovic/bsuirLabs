//
//  Pack.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Pack_hpp
#define Pack_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t MAX_SIZE_PACK_DATA = 150;
const size_t PACK_ADRESS_SIZE = 13;

struct Pack {
    unsigned long fstart;
    char recipient[PACK_ADRESS_SIZE];
    char sender[PACK_ADRESS_SIZE];
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
        ar & this->sizePack;
        ar & this->data;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->fstart;
        ar & this->recipient;
        ar & this->sender;
        ar & this->fother;
        ar & this->sizeData;
        ar & this->sizePack;
        ar & this->data;
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
