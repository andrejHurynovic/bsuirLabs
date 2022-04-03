//
//  Error.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Error_hpp
#define Error_hpp

#include <string>
#include <iostream>

namespace Error {
//    static void string_error(const std::string &msg) {
//
//    }

    static void char_arr_error(const char *msg) {
        std::cerr << "\n\t---Error\n";
        std::cerr << msg << std::endl;
    }
//
//    static void char_error(const char &msg) {
//
//    }
//
//    static void int_error(const int &num) {
//
//    }
}

#endif /* Error_hpp */
