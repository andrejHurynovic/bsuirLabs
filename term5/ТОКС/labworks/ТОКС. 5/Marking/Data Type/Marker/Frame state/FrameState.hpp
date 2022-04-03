//
//  FrameState.hpp
//  main
//
//  Created by Andrej Hurynovič on 15.11.21.
//

#ifndef FrameState_hpp
#define FrameState_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#define FRAME_COPIED_OFF 0
#define FRAME_COPIED_ON 1

struct FrameState {
    unsigned short AddressRecog;
    unsigned short FrameCopied;
    unsigned short Reserved;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->AddressRecog;
        ar & this->FrameCopied;
        ar & this->Reserved;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->AddressRecog;
        ar & this->FrameCopied;
        ar & this->Reserved;
    }

    void set_frame_copied(const unsigned int &flag) {
        this->FrameCopied = flag;
    }

    unsigned int get_frame_copied() const {
        return this->FrameCopied;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, const struct FrameState &FS) {
        out << "Address Recog: " << FS.AddressRecog << "\n";
        out << "Frame Copied: " << FS.FrameCopied << "\n";
        out << "Reserved: " << FS.Reserved << "\n";
        return out;
    }
};

#endif /* FrameState_hpp */
