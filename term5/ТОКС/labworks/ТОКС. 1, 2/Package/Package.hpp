//
//  Package.hpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#ifndef Package_hpp
#define Package_hpp

#include <array>
#include <typeinfo>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/split_member.hpp>

using namespace std;

const size_t packDataMaximalSize = 150;

struct Pack {
    unsigned long startPoint;
    unsigned long parent;
    size_t dataSize;
    char data[packDataMaximalSize];
    size_t packSize;
    
    template<class Archive>
    void save(Archive &archive) const {
        archive & this->startPoint;
        archive & this->parent;
        archive & this->dataSize;
        archive & this->packSize;
        archive & this->data;
    }
    
    template<class Archive>
    void load(Archive &archive) {
        archive & this->startPoint;
        archive & this->parent;
        archive & this->dataSize;
        archive & this->packSize;
        archive & this->data;
    }
    
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
    friend ostream& operator << (ostream &out, struct Pack &pack) {
        out << "Pack information: " << endl;
        out << "Parent: " << pack.parent << endl << endl;
        out << "Data: " << pack.data << endl << endl;
        out << "Start point: " << pack.startPoint << endl;
        out << "Data size: " << pack.dataSize << endl;
        out << "Pack size: " << pack.packSize << endl;
        return out;
    }
};

const size_t maxPackSize = sizeof(struct Pack) * 2 + 100; // 100 - boost reserved space

class Package {
private:
    struct Pack value;
    
public:
    constexpr Package() : value{} {}
    
    void start() noexcept;
    
    char* getData() noexcept;
    
    template <typename Type>
    void changeData(Type &data) {
        this->value.parent = typeid(data).hash_code();
        
        memset(this->value.data, '\0', packDataMaximalSize);
        memcpy(this->value.data, data, sizeof(data) * sizeof(*data));
        
        this->value.dataSize = sizeof(data);
    }
    
    template<class Archive>
    void save(Archive &archive) const {
        archive & this->value;
    }
    
    template<class Archive>
    void load(Archive &archive) {
        archive & this->value;
    }
    
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    
    friend ostream& operator<<(ostream &out, Package &P);
private:
    void setFlag() noexcept;
    void set_sender() noexcept;
    void set_recipiend() noexcept;
    void set_other_flag() noexcept;
    void set_size_pack() noexcept;
    
    friend class boost::serialization::access;
    
private:
    const unsigned long fstart = 02001;
};

#endif /* Package_hpp */
