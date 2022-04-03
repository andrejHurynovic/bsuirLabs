//
//  Marking.hpp
//  main
//
//  Created by Andrej Hurynovič on 15.11.21.
//

#ifndef Marking_hpp
#define Marking_hpp

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

#include "Status.hpp"
#include "Marker.hpp"

#include <sstream>
#include <string>


class Marking {
private:
    Marker value;

public:
    constexpr Marking() : value() {}

    void start();

    void set_source_adress(const std::string &adress);
    std::string get_source_adress() const;

    void set_destination_address(const std::string &adress);
    std::string get_destination_adress() const;

    void set_priority(const unsigned int &priority);
    unsigned int get_priority() const;

    void set_token(const unsigned int &token);
    unsigned int get_token() const;

    void set_reservation(const unsigned int &reserv);
    unsigned int get_reservation() const;

    void set_frame_status(const unsigned int &frame);
    unsigned int get_frame_status() const;

    void set_id(const unsigned int &id) noexcept;
    unsigned int get_id() const noexcept;

    void set_start_delimiter(const unsigned int &delimiter);
    unsigned int get_start_delimiter() const;

    void set_ending_delimiter(const unsigned int &delimiter);
    unsigned int get_ending_delimiter() const;

    void set_frame_check_sequence(const unsigned int &size);
    size_t get_frame_check_sequence() const;

    void set_inter_frame_gap();

    void set_regime(const unsigned int &regime);
    unsigned int get_regime() const;

    void set_data(const std::string &data) {
        memset(this->value.Data, '\0', sizeof(this->value.Data));
        memcpy(this->value.Data, data.c_str(), data.size());

        this->value.FrameCheckSequence = data.size();
    }

    const char* get_data() const noexcept;

private:
    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->value;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->value;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;

    friend std::ostream& operator<<(std::ostream &out, const Marking &M) {
        out << M.value;
        return out;
    }
};

#endif /* Marking_hpp */
