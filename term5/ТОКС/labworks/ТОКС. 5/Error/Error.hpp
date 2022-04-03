//
//  Error.hpp
//  LabWork_4
//
//  Created by Andrej Hurynovič on 28.10.21.
//

#ifndef Error_hpp
#define Error_hpp

#include <string>
#include <exception>

class Error : public std::exception {
private:
    std::string message;
public:
    explicit Error(const char* msg) : message(msg) {}
    explicit Error(const std::string &msg) : message(msg) {}

    virtual ~Error() noexcept {}

    virtual const char* what() const noexcept {
        return message.c_str();
    }
};

#endif /* Error_hpp */
