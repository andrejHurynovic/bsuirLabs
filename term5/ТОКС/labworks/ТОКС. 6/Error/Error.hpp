//
//  Error.hpp
//  LabWorkc_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef Error_hpp
#define Error_hpp

#include <string>
#include <exception>

class Error : public std::exception {
private:
    std::string message;
    std::string function;
public:
    explicit Error(const char* where, const char* msg) : message(msg) {}
    explicit Error(const std::string &msg) : message(msg) {}

    virtual ~Error() noexcept {}

    virtual const char* what() const noexcept {
        return message.c_str();
    }
};


#endif /* Error_hpp */
