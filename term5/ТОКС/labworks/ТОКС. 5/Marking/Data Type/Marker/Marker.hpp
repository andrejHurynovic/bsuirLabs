//
//  Marker.hpp
//  main
//
//  Created by Andrej Hurynovič on 15.11.21.
//

#ifndef Marker_hpp
#define Marker_hpp

#include "Access.hpp"
#include "FrameState.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#define MSG_TYPE 1
#define FRAME_TYPE 2

#define EARLY_RELEASE_OFF 0
#define EARLY_RELEASE_ON 1

const size_t ADRESS_SIZE = 13;
const size_t MAX_SIZE_MSG_DATA = 150;

struct Marker {
    unsigned int StartingDelimiter;
    Access AccessControl;
    char DestinationAddress[ADRESS_SIZE];
    char SourceAddress[ADRESS_SIZE];
    char Data[MAX_SIZE_MSG_DATA];
    size_t FrameCheckSequence;
    unsigned int EndingDelimiter;
    FrameState FrameStatus;
    unsigned int InterFrameGap;
    unsigned int Id;
    unsigned int Regime;

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->StartingDelimiter;
        ar & this->AccessControl;
        ar & this->DestinationAddress;
        ar & this->SourceAddress;
        ar & this->Data;
        ar & this->FrameCheckSequence;
        ar & this->InterFrameGap;
        ar & this->Id;
        ar & this->Regime;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->StartingDelimiter;
        ar & this->AccessControl;
        ar & this->DestinationAddress;
        ar & this->SourceAddress;
        ar & this->Data;
        ar & this->FrameCheckSequence;
        ar & this->InterFrameGap;
        ar & this->Id;
        ar & this->Regime;
    }


    void set_frame_status(const unsigned int &flag) {
        this->FrameStatus.set_frame_copied(flag);
    }

    unsigned int get_frame_status() const {
        return this->FrameStatus.get_frame_copied();
    }

    void set_priority_bit(const unsigned int &priority) {
        this->AccessControl.set_priority_bit(priority);
    }

    void set_token_bit(const unsigned int &token) {
        this->AccessControl.set_token_bit(token);
    }

    void set_reservation_bit(const unsigned int &reserv) {
        this->AccessControl.set_reservation_bit(reserv);
    }

    unsigned int get_priority_bit() const {
        return this->AccessControl.get_priority_bit();
    }

    unsigned int get_token_bit() const {
        return this->AccessControl.get_token_bit();
    }

    unsigned int get_reservation_bit() const {
        return this->AccessControl.get_reservation_bit();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, const struct Marker &M) {
        out << "\n\t---Marker---\n";
        out << "Starting Delimiter: " << M.StartingDelimiter << "\n";
        out << "\tAccess Control\n"  << M.AccessControl << "\t----------\n";
        out << "Destination Address: " << M.DestinationAddress << "\n";
        out << "Source Address: " << M.SourceAddress << "\n";
        out << "Data: " << M.Data << "\n";
        out << "Frame Check Sequence: " << M.FrameCheckSequence << "\n";
        out << "Ending Delimiter: " << M.EndingDelimiter << "\n";
        out << "\tFrame Status\n" << M.FrameStatus << "\t----------\n";
        out << "Inter Frame Gap: " << M.InterFrameGap << "\n";
        out << "\t---END MARKER---\n";
        return out;
    }
};

#endif /* Marker_hpp */
