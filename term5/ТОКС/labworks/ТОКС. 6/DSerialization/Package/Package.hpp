//
//  Package.hpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef Package_hpp
#define Package_hpp

#include "IPv4.hpp"
#include "Pack.hpp"
#include "DSerialization.hpp"

#include <typeinfo>

const size_t MAX_SIZE_PACK = (sizeof(Pack) + 100) * 2;

class Package {
private:
    struct Pack value;
    IPv4 sender;
    IPv4 recipient;

public:
    constexpr Package() : sender{}, recipient{}, value{} {}
    constexpr Package(const IPv4 &sender, const IPv4 &recipient) : sender{sender}, recipient{recipient}, value{} {}

//    Package& operator=(const Package P) {
//        this->value = P.value;
//        this->sender = P.sender;
//        this->recipient = P.recipient;
//        return *this;
//    }

    void start() noexcept;

    char* get_data() noexcept;

    void change_sender(const IPv4 &sender) noexcept;
    void change_recipiend(const IPv4 &recipiend) noexcept;

    template <typename Type>
    void change_data(Type &data) {
        this->value.fother = typeid(data).hash_code();

        memset(this->value.data, '\0', MAX_SIZE_PACK_DATA);
        memcpy(this->value.data, data, sizeof(data) * sizeof(*data));

        this->value.sizeData = sizeof(data);
    }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & this->value;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & this->value;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    friend std::ostream& operator<<(std::ostream &out, Package &P);
//    friend std::istream& operator<<(std::istream &in, Package &P);
private:
    void set_flag() noexcept;
    void set_sender() noexcept;
    void set_recipiend() noexcept;
    void set_other_flag() noexcept;
    void set_size_pack() noexcept;

    friend class boost::serialization::access;

private:
    const unsigned long fstart = 02001;
};

#endif /* Package_hpp */
