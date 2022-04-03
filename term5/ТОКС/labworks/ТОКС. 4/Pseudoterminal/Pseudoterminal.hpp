//
//  Pseudoterminal.hpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#ifndef Pseudoterminal_hpp
#define Pseudoterminal_hpp

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <map>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>

#include "PseudoterminalSettings.hpp"
#include "PStatus.hpp"
//#include "PLastAction"

class Pseudoterminal {
private:
    int descriptor;
    std::string port;

    PseudoterminalSettings *settings;
    
    int counter;

    std::map<unsigned int, std::pair<std::string, int>> lnetwork;
    std::stringstream buffer;
public:
    Pseudoterminal();
    ~Pseudoterminal();

    bool create_port();
    std::string get_port_name();

    bool connect(const std::string &port);
    bool accept_connect(const std::string &port);

    void disconnect(const unsigned int &device);
    void accept_disconnect(const unsigned int &device);

    std::map<unsigned int, std::pair<std::string, int>> get_list_network() const;
    size_t get_count_connect() const;

    std::string read_port(const std::size_t &size);
    size_t write_port(const std::string &str, const unsigned int &device);
    
    void resending(const std::string &port);
    void collision();

    void change_speed_in(const size_t &speed);
    void change_speed_out(const size_t &speed);

    void close_port();
    bool is_open();

    int find_device(const std::string &port) const;
private:
    void init_port_settings();
    void flush_port_buffer();

    void wait() const noexcept;
//    void error(std::string msg);
};

#endif /* Pseudoterminal_hpp */
