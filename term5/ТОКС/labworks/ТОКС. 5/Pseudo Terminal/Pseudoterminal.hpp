//
//  Pseudoterminal.hpp
//  LabWork_4
//
//  Created by Andrej Hurynovič on 28.10.21.
//

#ifndef Pseudoterminal_hpp
#define Pseudoterminal_hpp

#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <queue>
#include <fstream>

#include "PseudoterminalSettings.hpp"
#include "Marking.hpp"
#include "ThreadControl.hpp"

#define SIZE_READ_PORT 1024

class Pseudoterminal {
protected:
    int descriptor;
    std::string port;
    PseudoterminalSettings *settings;

    std::pair<std::string, int> connectedDevice;

    std::queue<std::pair<std::string, std::string>> queueWrite;
    std::queue<std::string> queueRead;

    std::thread reader, writer;
    unsigned int fread, fwrite;
    std::mutex mutRead, mutWrite;
    std::condition_variable condition;

    Marking marker;

    unsigned int skip_data;
    unsigned int accepted_data;
    unsigned int write_data_count;
public:
    Pseudoterminal();
    ~Pseudoterminal();

    void create_port();
    unsigned int create_terminal();

    std::string get_port_name();

    bool connect(const std::string &port);
    void disconnect();

    std::string read_port(const std::size_t &size);
    size_t write_port(const std::string &str);

    void change_speed_in(const size_t &speed);
    void change_speed_out(const size_t &speed);

    void close_port();
    bool is_open();
    bool is_connected();

    void add_to_queue_write(const std::string &name, const std::string &value);
    void add_to_queue_read(const std::string value);

    std::string get_data_queue_read();

protected:
    void init_settings();

    virtual void thread_start();
    void thread_stop();

    virtual void thread_read();
    void thread_write();

    void wait() const noexcept;

    void set_marker_param();
    void free_marker();
    void accept_data();

    void get_status(const std::string &buffer);
};

#endif /* Pseudoterminal_hpp */
