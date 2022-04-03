//
//  Frame.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Frame_hpp
#define Frame_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

const size_t MAX_SIZE_FRAME_DATA = 150;
const size_t FRAME_ADRESS_SIZE = 13;

struct Frame {
    long int preamble;
    char SFD;
    char DA[FRAME_ADRESS_SIZE];
    char SA[FRAME_ADRESS_SIZE];
    size_t size;
    char data[MAX_SIZE_FRAME_DATA];
    size_t FCS;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->preamble;
        ar & this->SFD;
        ar & this->DA;
        ar & this->SA;
        ar & this->size;
        ar & this->data;
        ar & this->FCS;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->preamble;
        ar & this->SFD;
        ar & this->DA;
        ar & this->SA;
        ar & this->size;
        ar & this->data;
        ar & this->FCS;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, struct Frame &F) {
        out << "\t---FRAME---\n";
        out << "Preamble: " << F.preamble << "\n";
        out << "SFD: " << F.SFD << "\n";
        out << "DS: " << F.DA << "\n";
        out << "SA: " << F.SA << "\n";
        out << "Size: " << F.size << "\n";
        out << "Data: " << F.data << "\n";
        out << "FCS: " << F.FCS << "\n";
        out << "\t---END FRAME---\n";
        return out;
    }

};

#endif /* Frame_hpp */
